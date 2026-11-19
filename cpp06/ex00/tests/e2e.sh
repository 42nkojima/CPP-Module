#!/bin/sh

# どこから実行してもバイナリを見つけられるよう、スクリプト位置を基準に解決する。
BIN="$(cd "$(dirname "$0")/.." && pwd)/convert"

# 色付け (FD先がターミナルでなければ無効化)
if [ -t 1 ]; then
  GREEN=$(printf '\033[32m'); RED=$(printf '\033[31m')
  DIM=$(printf '\033[2m');    RESET=$(printf '\033[0m')
else
  GREEN=; RED=; DIM=; RESET=
fi

# バイナリが「存在して実行可能である」かをチェック
if [ ! -x "$BIN" ]; then
  printf '%sconvert not found — run `make` first%s\n' "$RED" "$RESET"
  exit 1
fi

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

# lines <char> <int> <float> <double>
# 各行の値から、convert が出すはずの 4 行を組み立てる。
lines() {
  printf 'char: %s\nint: %s\nfloat: %s\ndouble: %s' "$1" "$2" "$3" "$4"
}

# check <入力> <char> <int> <float> <double>
check() {
  input="$1"; shift
  report "<$input>" "$(lines "$@")" "$("$BIN" "$input" 2>&1)"
}

# check_invalid <入力>
# リテラルとして受け付けない入力は、4 行とも impossible になる。
check_invalid() {
  check "$1" impossible impossible impossible impossible
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

# ==========
# 引数の個数
# ==========

check_status 1
check_status 1 1 2
check_status 0 42

# ============
# 課題文の実行例
# ============

check 0     'Non displayable' 0          0.0f  0.0
check nan   impossible        impossible nanf  nan
check 42.0f "'*'"             42         42.0f 42.0

# ====
# char
# ====

check a   "'a'" 97 97.0f 97.0
check '*' "'*'" 42 42.0f 42.0
check ' ' "' '" 32 32.0f 32.0

# 数字ではない 1 文字は、記号でも char として読む。
check - "'-'" 45 45.0f 45.0
check . "'.'" 46 46.0f 46.0

# ===
# int
# ===

check 42  "'*'"             42  42.0f  42.0
check +42 "'*'"             42  42.0f  42.0
check -42 'Non displayable' -42 -42.0f -42.0

# 数字 1 文字は char ではなく int として読む。
check 7 'Non displayable' 7 7.0f 7.0

# --- char に収まるかの境界 ---

check 126 "'~'"             126 126.0f 126.0
check 127 'Non displayable' 127 127.0f 127.0
check 128 impossible        128 128.0f 128.0

# --- int の両端 ---

# float は 2147483647 を正確に表せないので、いちばん近い 2147483648 になる。
check 2147483647  impossible 2147483647  2147483648.0f  2147483647.0
check -2147483648 impossible -2147483648 -2147483648.0f -2147483648.0

# --- int に収まらない整数は double として読む ---

check 2147483648  impossible impossible 2147483648.0f  2147483648.0
check -2147483649 impossible impossible -2147483648.0f -2147483649.0

# =====
# float
# =====

check 0.0f  'Non displayable' 0  0.0f  0.0
check 97.0f "'a'"             97 97.0f 97.0

# float は 4.2 を正確に表せない。double の行には、float が実際に持っている値が出る。
check 4.2f  'Non displayable' 4  4.2f  4.19999980926514
check -4.2f 'Non displayable' -4 -4.2f -4.19999980926514

# 小数点の片側に数字がなくても受け付ける。
check 4.f 'Non displayable' 4 4.0f 4.0
check .5f 'Non displayable' 0 0.5f 0.5

# --- 疑似リテラル ---

check nanf  impossible impossible nanf  nan
check +inff impossible impossible +inff +inf
check -inff impossible impossible -inff -inf

# --- float に収まらない float の形は double として読む ---

# float の最大値は、そのまま float として読める。
FLT_MAX=340282346638528859811704183484516925440
check "$FLT_MAX.0f" impossible impossible "$FLT_MAX.0f" "$FLT_MAX.0"

# その 10 倍は float に収まらない。
check "${FLT_MAX}0.0f" impossible impossible impossible "${FLT_MAX}0.0"

# ======
# double
# ======

check 0.0  'Non displayable' 0  0.0f  0.0
check 4.2  'Non displayable' 4  4.2f  4.2
check -4.2 'Non displayable' -4 -4.2f -4.2
check 42.0 "'*'"             42 42.0f 42.0

check 4. 'Non displayable' 4 4.0f 4.0
check .5 'Non displayable' 0 0.5f 0.5

# --- 疑似リテラル ---

check +inf impossible impossible +inff +inf
check -inf impossible impossible -inff -inf

# --- double にも収まらない数値は受け付けない ---

# ラベルが長くなりすぎるので、check を使わず直接比べる。
HUGE=$(printf '%0400d' 0 | tr 0 9)
INVALID=$(lines impossible impossible impossible impossible)
report '<9 を 400 桁>'      "$INVALID" "$("$BIN" "$HUGE" 2>&1)"
report '<9 を 400 桁 + .0f>' "$INVALID" "$("$BIN" "$HUGE.0f" 2>&1)"

# ==========
# 小数の桁数
# ==========

# float は有効数字 6 桁、double は 15 桁まで出す。入力した桁は丸めない。
check 42.25 "'*'"             42 42.25f 42.25
check 4.25f 'Non displayable' 4  4.25f  4.25
check 1.99  'Non displayable' 1  1.99f  1.99
check 0.04  'Non displayable' 0  0.04f  0.04
check -0.04 'Non displayable' 0  -0.04f -0.04

# 小さい値も 0.0 にしない。
check 0.00001 'Non displayable' 0 0.00001f 0.00001

# float の 6 桁を超える分は、float の行だけ丸められる。
check 3.14159265358979 'Non displayable' 3 3.14159f 3.14159265358979

# 整数の値には .0 を付ける。
check 100.0 "'d'" 100 100.0f 100.0

# ======================
# 受け付けない入力
# ======================

check_invalid ''
check_invalid abc
check_invalid ab

# --- 数値の形が崩れている ---

check_invalid 42f
check_invalid 4.2ff
check_invalid 4.2.1
check_invalid -.
check_invalid --42
check_invalid +-42
check_invalid 4-2

# --- 前後の空白 ---

check_invalid ' 42'
check_invalid '42 '

# --- 10 進の小数以外の書き方 ---

check_invalid 1e5
check_invalid 0x2A

# --- 課題文にない形の疑似リテラル ---

check_invalid inf
check_invalid inff
check_invalid NaN
check_invalid nanff
check_invalid +nan

# --- 引用符ごと渡された char ---

check_invalid "'a'"

# ======
# サマリ
# ======
total=$((pass + fail))
printf '\n%d tests: %s%d passed%s' "$total" "$GREEN" "$pass" "$RESET"
[ "$fail" -gt 0 ] && printf ', %s%d failed%s' "$RED" "$fail" "$RESET"
printf '\n'

[ "$fail" -eq 0 ]
