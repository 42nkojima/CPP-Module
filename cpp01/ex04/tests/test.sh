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

# --- 引数の個数 -------------------------------------------------------------

check_status 1
check_status 1 file
check_status 1 file s1
check_status 1 file s1 s2 extra

# --- 入力ファイルが開けない -------------------------------------------------

check_status 1 "$WORK/does-not-exist" a b

# ディレクトリは open できてしまう環境があるため、読み取り不可のファイルで確認する。
printf 'secret\n' > "$WORK/noperm.txt"
chmod 000 "$WORK/noperm.txt"
# root は権限を無視できるので、その場合はこのケースを飛ばす。
if [ ! -r "$WORK/noperm.txt" ]; then
  check_status 1 "$WORK/noperm.txt" a b
fi
chmod 644 "$WORK/noperm.txt"

# --- 正常系 -----------------------------------------------------------------

printf 'hello world\n' > "$WORK/input.txt"
check_status 0 "$WORK/input.txt" hello hi

# サマリ
total=$((pass + fail))
printf '\n%d tests: %s%d passed%s' "$total" "$GREEN" "$pass" "$RESET"
[ "$fail" -gt 0 ] && printf ', %s%d failed%s' "$RED" "$fail" "$RESET"
printf '\n'

[ "$fail" -eq 0 ]
