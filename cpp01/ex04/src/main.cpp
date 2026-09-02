// 入出力の実装方針
// 1. 引数を検証する (個数、内容)
// 2. 入力ファイルを開く -> 開けたか確認する
// 3. 中身を全部読む
// 4. 置換して新しい文字列を作る
// 5. <filename>.replace を開く -> 開けたか確認する
// 6. 書き出す

//やること ./replace <filename> <s1> <s2>
//1. <filename> を開く
//2. 中身を全部読む
//3. s1 の全出現を s2 に置換
//4. 結果を <filename>,replace という新ファイルに書き出す

// point:
// 開けたか確認しないと、失敗した状態のまま処理が進む。ストリームが成功/失敗を教えてくれる仕組みがあるぽい

// エラーとして扱うべきケース
//- 引数の個数が違う (多い/少ない)
//- 入力ファイルが開けない (存在しない、権限がない)
//- 出力ファイルが作れない
//- s1が空文字列
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main(int ac, char** av) {
  if (ac != 4) {
    std::cerr << "usage: " << av[0] << " <filename> <s1> <s2>\n";
    return 1;
  }

  // todo: ここから下を書き換える
  // - s1 (av[2]) が空なら エラーにして return 1 (test.sh がこれを期待している)
  // - Replacer(av[2], av[3]) と FileReplacer(av[1], replacer) を作る
  // - Execute() の戻り値で return 0 / 1 を決める
  // - 下の ifstream 〜 oss は FileReplacer::Execute() へ引っ越す
  // - 引っ越し後は <fstream> <sstream> がここでは不要になる
  // - 代わりに "Replacer.hpp" と "FileReplacer.hpp" を include する
  // - "nonexistent filename" は権限で開けない場合にも出るので文言を直す

  std::string filename = av[1];

  std::ifstream ifs(filename.c_str());
  if (!ifs) {
    std::cerr << "nonexistent filename " << filename << "\n";
    return 1;
  }

  std::ostringstream oss;

  oss << ifs.rdbuf();  // ifs の中身を oss へ流し込む
  std::string content = oss.str();

  std::cout << content;

  return 0;
}
