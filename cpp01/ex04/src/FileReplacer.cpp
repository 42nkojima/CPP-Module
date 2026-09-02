#include "FileReplacer.hpp"

FileReplacer::FileReplacer(const std::string& filename,
                           const Replacer& replacer)
    : filename_(filename), replacer_(replacer) {}

bool FileReplacer::Execute() const {
    //todo:
    //1. filename_ を開く -> if (!ifs) で開けたか確認
    //2. 中身を全部読む
    //3. replacer_.Apply()に通す
    //4. filename_ + ".replace" を開く -> if (!ofs) で作れたか確認
    //5. 書き出す
    //6. 成否を bool で返す

    //メモ:
    //- 1,2 は main.cpp に書いたコードをそのまま移す (filename -> filename_)
    //- 4,5 は ofstream で同じ形。ofs << content で書ける
    //- 必要なヘッダは <fstream> と <sstream>
    //- close は書かない。スコープを抜けるとデストラクタが閉じる (RAII)
    //- ストリームは失敗しても例外を投げず、失敗状態のオブジェクトになるだけ。
    //  だから開いた直後に必ず聞く

    //エラーの分担:
    //- ここでは何が失敗したかを stderr に出して false を返す
    //- その結果どの終了コードにするかは main が決める
}
