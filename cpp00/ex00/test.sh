#!/bin/sh

# 色付け (FD先がターミナルでなければ無効化)
if [ -t 1 ]; then
  GREEN=$(printf '\033[32m'); RED=$(printf '\033[31m')
  DIM=$(printf '\033[2m');    RESET=$(printf '\033[0m')
else
  GREEN=; RED=; DIM=; RESET=
fi

# バイナリが「存在して実行可能である」かをチェック
if [ ! -x ./megaphone ]; then
  printf '%s./megaphone not found — run `make` first%s\n' "$RED" "$RESET"
  exit 1
fi

pass=0
fail=0

# check <期待値> <入力...>
check() {
  expected="$1"; shift

  # 入力を <arg> 単位で囲って連結 (境界と空文字を明示)
  args=
  for a in "$@"; do args="$args<$a>"; done
  [ -z "$args" ] && args="(no args)"

  actual="$(./megaphone "$@")"

  if [ "$actual" = "$expected" ]; then
    pass=$((pass + 1))
    printf '%sPASS%s  %s\n' "$GREEN" "$RESET" "$args"
  else
    fail=$((fail + 1))
    printf '%sFAIL%s  %s\n' "$RED" "$RESET" "$args"
    printf '      %sexpected%s [%s]\n' "$DIM" "$RESET" "$expected"
    printf '      %sactual  %s [%s]\n' "$DIM" "$RESET" "$actual"
  fi
}

check "SHHHHH... I THINK THE STUDENTS ARE ASLEEP..." \
  "shhhhh... I think the students are asleep..."

check "DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF." \
  Damnit " ! " "Sorry students, I thought this thing was off."

check "* LOUD AND UNBEARABLE FEEDBACK NOISE *"

# サマリ
total=$((pass + fail))
printf '\n%d tests: %s%d passed%s' "$total" "$GREEN" "$pass" "$RESET"
[ "$fail" -gt 0 ] && printf ', %s%d failed%s' "$RED" "$fail" "$RESET"
printf '\n'

[ "$fail" -eq 0 ]
