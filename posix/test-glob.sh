#! /bin/sh

#common_objpfx=$1; shift
#elf_objpfx=$1; shift
#rtld_installed_name=$1; shift

# We have to make the paths `common_objpfx' absolute.
#case "$common_objpfx" in
#  .*)
#    common_objpfx="`pwd`/$common_objpfx"
#    ;;
#  *)
#    ;;
#esac

# We have to find the libc and the NSS modules.
#library_path=${common_objpfx}:${common_objpfx}nss:${common_objpfx}nis:${common_objpfx}db2:${common_objpfx}hesiod

# Since we use `sort' we must make sure to use the same locale everywhere.
LC_ALL=C
export LC_ALL
LANG=C
export LANG

# Create the arena
: ${TMPDIR=/tmp}
testdir=$TMPDIR/globtest-dir
testout=$TMPDIR/globtest-out

trap 'rm -fr $testdir $testout' 1 2 3 15

rm -fr $testdir
mkdir $testdir
echo 1 > $testdir/file1
echo 2 > $testdir/file2
echo 3 > $testdir/-file3
echo 4 > $testdir/~file4
echo 5 > $testdir/.file5
echo 6 > $testdir/'*file6'
mkdir $testdir/dir1
mkdir $testdir/dir2
echo 1_1 > $testdir/dir1/file1_1
echo 1_2 > $testdir/dir1/file1_2

# Run some tests.
result=0

# Normal test
./test-glob "$testdir" "*" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`*file6'
`-file3'
`dir1'
`dir2'
`file1'
`file2'
`~file4'
EOF

# Don't let glob sort it
./test-glob -s "$testdir" "*" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`*file6'
`-file3'
`dir1'
`dir2'
`file1'
`file2'
`~file4'
EOF

# Mark directories
./test-glob -m "$testdir" "*" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`*file6'
`-file3'
`dir1/'
`dir2/'
`file1'
`file2'
`~file4'
EOF

# Find files starting with .
./test-glob -p "$testdir" "*" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`*file6'
`-file3'
`.'
`..'
`.file5'
`dir1'
`dir2'
`file1'
`file2'
`~file4'
EOF

# Test braces
./test-glob -b "$testdir" "file{1,2}" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`file1'
`file2'
EOF

# Test NOCHECK
./test-glob -c "$testdir" "abc" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`abc'
EOF

# Test NOMAGIC without magic characters
./test-glob -g "$testdir" "abc" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`abc'
EOF

# Test NOMAGIC with magic characters
./test-glob -g "$testdir" "abc*" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
GLOB_NOMATCH
EOF

# Test subdirs correctly
./test-glob "$testdir" "*/*" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`dir1/file1_1'
`dir1/file1_2'
EOF

# Test subdirs for invalid names
./test-glob "$testdir" "*/1" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
GLOB_NOMATCH
EOF

# Test subdirs with wildcard
./test-glob "$testdir" "*/*1_1" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`dir1/file1_1'
EOF

# Test subdirs with ?
./test-glob "$testdir" "*/*?_?" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`dir1/file1_1'
`dir1/file1_2'
EOF

./test-glob "$testdir" "*/file1_1" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`dir1/file1_1'
EOF

./test-glob "$testdir" "*-/*" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
GLOB_NOMATCH
EOF

./test-glob "$testdir" "*-" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
GLOB_NOMATCH
EOF

# Test subdirs with ?
./test-glob "$testdir" "*/*?_?" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`dir1/file1_1'
`dir1/file1_2'
EOF

# Test tilde expansion
./test-glob -q -t "$testdir" "~" |
sort >$testout
echo ~ | cmp - $testout || result=1

# Test tilde expansion with trailing slash
./test-glob -q -t "$testdir" "~/" |
sort > $testout
echo ~/ | cmp - $testout || result=1

# Test tilde expansion with username
./test-glob -q -t "$testdir" "~"$USER |
sort > $testout
eval echo ~$USER | cmp - $testout || result=1

# Tilde expansion shouldn't match a file
./test-glob -T "$testdir" "~file4" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
GLOB_NOMATCH
EOF

# Matching \** should only find *file6
./test-glob "$testdir" "\**" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`*file6'
EOF

# ... unless NOESCAPE is used, in which case it shouldn't match anything.
./test-glob -e "$testdir" "\**" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
GLOB_NOMATCH
EOF

# Try a recursive failed search
./test-glob -e "$testdir" "a*/*" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
GLOB_NOMATCH
EOF

# Try multiple patterns (GLOB_APPEND)
./test-glob "$testdir" "file1" "*/*" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`dir1/file1_1'
`dir1/file1_2'
`file1'
EOF

# Try multiple patterns (GLOB_APPEND) with offset (GLOB_DOOFFS)
./test-glob -o "$testdir" "file1" "*/*" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`abc'
`dir1/file1_1'
`dir1/file1_2'
`file1'
EOF

# Test NOCHECK with non-existing file in subdir.
./test-glob -c "$testdir" "*/blahblah" |
sort > $testout
cat <<"EOF" | cmp - $testout || result=1
`dir1/blahblah'
`dir2/blahblah'
EOF

if test $result -eq 0; then
    rm -fr $testdir $testout
fi

exit $result

# Preserve executable bits for this shell script.
Local Variables:
eval:(defun frobme () (set-file-modes buffer-file-name file-mode))
eval:(make-local-variable 'file-mode)
eval:(setq file-mode (file-modes (buffer-file-name)))
eval:(make-local-variable 'after-save-hook)
eval:(add-hook 'after-save-hook 'frobme)
End:
