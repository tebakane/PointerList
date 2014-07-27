PointerList
===========

C言語用List関数

#### InitPList()
PList構造体作成

#### FinalPList(PList \*list)
PList構造体削除

#### AddPList(PList \*list, void \*val)
PList構造体に新しくvalポインターを追加


#### DeletePList(PList \*list, int index)
PList構造体からindexの位置を削除

#### forlist
forlistはPListから一つずつ取り出して使用する。

KeyValueList
============

C言語用KVList関数

#### InitKVList()
KVList構造体作成

#### FinalKVList(KVList \*list)
KVList構造体削除

#### AddKVList(KVList \*list, char \*key, void \*val)
list に key に val をセットする(SetKVListと同じ)
keyに既に値がセットされている場合はvalを上書きする。
AddKVList内ではvalの領域の再確保は行われないので外でfreeされれば
中のvalもfreeされた状態になるので注意

#### DeleteKVKist(KVList \*list, char \*key)
list から key を削除する。key が存在しない場合はなにもしない。

#### GetValueKVList(KVList \*list, char \*key)
list から key の val を取得する。keyが存在しない場合は NULL を返す。

#### GetKeysKVList(KVList \*list)
list の key一覧を取得する。PList\*で戻る。

#### GetValuesKVList(KVList \*list)
list の value一覧を取得する。PList\*で戻る。

#### IsKeyExistsKVList(KVList \*list, const char \*key)
list に key が存在するかを確認する。


sample/main.cを参照のこと

