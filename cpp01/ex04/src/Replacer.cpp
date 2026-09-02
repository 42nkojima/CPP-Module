#include "Replacer.hpp"

Replacer::Replacer(const std::string& from, const std::string& to)
    : from_(from), to_(to) {}

std::string Replacer::Apply(const std::string& content) const {
  // from_ が空文字列の場合のガードを書いて、単体テストできるようにする

  // find - 部分文字列を探して、見つかった位置を返す。
  // 見つからなかったら npos っていう値が返ってくる

  // substr - 部分文字列を切り出す。

  std::string result;
  // 1. from_ の位置を探す
  // 2. 見つかったら、その手前までを result に足して、 to_ を足す
  // 3. 次の探索開始位置を進める -> pos + from_.length()
  // 4. 見つからなくなったら、残り全部を result に足して終了

  return result;
}
