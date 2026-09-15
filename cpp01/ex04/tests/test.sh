#!/bin/sh

# どこから実行してもバイナリを見つけられるよう、スクリプト位置を基準に解決する。
BIN="$(cd "$(dirname "$0")/.." && pwd)/replace"

# 色付け (FD先がターミナルでなければ無効化)
if [ -t 1 ]; then
  GREEN=$(printf '\033[32m'); RED=$(printf '\033[31m')
  DIM=$(printf '\033[2m');    RESET=$(printf '\033[0m')
else
  GREEN=; RED=; DIM=; RESET=
fi

# バイナリが「存在して実行可能である」かをチェック
if [ ! -x "$BIN" ]; then
  printf '%sreplace not found — run `make` first%s\n' "$RED" "$RESET"
  exit 1
fi

# 生成物を作業ディレクトリに散らかさないよう、専用の一時ディレクトリで実行する。
WORK=$(mktemp -d)
trap 'rm -rf "$WORK"' EXIT

pass=0
fail=0

report() {
  label="$1"; expected="$2"; actual="$3"
  if [ "$actual" = "$expected" ]; then
    pass=$((pass + 1))
    printf '%sPASS%s  %s\n' "$GREEN" "$RESET" "$label"
  else
    fail=$((fail + 1))
    printf '%sFAIL%s  %s\n' "$RED" "$RESET" "$label"
    printf '      %sexpected%s [%s]\n' "$DIM" "$RESET" "$expected"
    printf '      %sactual  %s [%s]\n' "$DIM" "$RESET" "$actual"
  fi
}

# check_status <期待する終了ステータス> <引数...>
check_status() {
  expected="$1"; shift

  args=
  for a in "$@"; do args="$args<$a>"; done
  [ -z "$args" ] && args="(no args)"

  "$BIN" "$@" >/dev/null 2>&1
  report "exit $expected  $args" "$expected" "$?"
}

# check_content <入力の中身> <s1> <s2> <期待する中身>
# 入力を作り直してから実行するので、前のケースの .replace が残っていても影響しない。
# 中身は printf に渡すので \n が使える。
check_content() {
  input_text="$1"; s1="$2"; s2="$3"; expected="$4"

  f="$WORK/case.txt"
  rm -f "$f" "$f.replace"
  printf '%b' "$input_text" > "$f"

  "$BIN" "$f" "$s1" "$s2" >/dev/null 2>&1

  label="content  [$input_text] <$s1> -> <$s2>"
  if [ ! -f "$f.replace" ]; then
    report "$label" "$expected" "(.replace が作られていない)"
    return
  fi
  report "$label" "$expected" "$(cat "$f.replace")"
}

# 異常系・正常系の両方で使い回す入力ファイル。
printf 'hello world\n' > "$WORK/input.txt"

# ====================
# 異常系 (すべて exit 1)
# ====================

# --- 引数の個数 ---

check_status 1
check_status 1 file
check_status 1 file s1
check_status 1 file s1 s2 extra

# --- s1 が空 ---

check_status 1 "$WORK/input.txt" "" b

# --- 入力ファイルが開けない ---

check_status 1 "$WORK/does-not-exist" a b

# ディレクトリは open できてしまう環境があるため
printf 'secret\n' > "$WORK/noperm.txt"
chmod 000 "$WORK/noperm.txt"
# root は権限を無視できるので
if [ ! -r "$WORK/noperm.txt" ]; then
  check_status 1 "$WORK/noperm.txt" a b
fi
chmod 644 "$WORK/noperm.txt"

# --- 出力ファイルが作れない ---

# 書き込み不可のディレクトリの中の入力なら、<file>.replace を作れない。
mkdir -p "$WORK/readonly"
printf 'hello\n' > "$WORK/readonly/input.txt"
chmod 500 "$WORK/readonly"
# root は権限を無視できるので
if [ ! -w "$WORK/readonly" ]; then
  check_status 1 "$WORK/readonly/input.txt" hello hi
fi
chmod 700 "$WORK/readonly"

# ===============
# 正常系 (exit 0)
# ===============

check_status 0 "$WORK/input.txt" hello hi

# --- 置換結果 ---

check_content 'hello world' hello hi   'hi world'
check_content 'banana'      an    X    'bXXa'
check_content 'aaa'         a     b    'bbb'
check_content 'hello world' zzz   X    'hello world'
check_content 'aaa'         a     ''   ''
check_content 'xax'         a     ''   'xx'
check_content 'aa'          aa    bb   'bb'

# s1 と s2 が同じ。置換後の文字列を再び探してしまうと終わらなくなる。
check_content 'abc'         abc   abc  'abc'

# --- 元ファイルを書き換えていないこと ---

printf 'hello world\n' > "$WORK/orig.txt"
"$BIN" "$WORK/orig.txt" hello hi >/dev/null 2>&1
report "元ファイルが無傷" "hello world" "$(cat "$WORK/orig.txt")"

# --- 末尾の改行が保たれること ---

# $(...) は末尾の改行を落とすため check_content では見えない。ここだけバイト単位で比べる。
printf 'hello world\n' > "$WORK/nl.txt"
"$BIN" "$WORK/nl.txt" hello hi >/dev/null 2>&1
printf 'hi world\n' > "$WORK/nl.expected"
if cmp -s "$WORK/nl.expected" "$WORK/nl.txt.replace"; then
  nl_result=一致
else
  nl_result=不一致
fi
report "末尾の改行が保たれる (バイト単位)" "一致" "$nl_result"

# ======
# サマリ
# =====
total=$((pass + fail))
printf '\n%d tests: %s%d passed%s' "$total" "$GREEN" "$pass" "$RESET"
[ "$fail" -gt 0 ] && printf ', %s%d failed%s' "$RED" "$fail" "$RESET"
printf '\n'

[ "$fail" -eq 0 ]
