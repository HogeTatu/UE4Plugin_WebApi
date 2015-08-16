SimpleGet
==================================

シンプルなGET通信サンプルです。

## 手順

### 接続先を作成

サーバー上に info.php を配置します。

### Web API クラス定義

Blueprint で WebApi クラスを継承した BP_WebApiGet クラスを作成します。

ClassDefaults から接続先の Url を任意のものに変更します。

![SimpleGet_01.jpg](/Examples/01_SimpleGet/SimpleGet_01.jpg)

### Web API 呼び出し

以下の画像を参考に Web API 呼び出しを記述します。

1. WebApi のインスタンスを作成
* リクエスト処理成功時イベント（OnRequestSuccessed）にイベントを追加
* OnRequestSuccessed 内で文字列形式レスポンス（WebApiResponseBodyString）へキャストし、レスポンスを出力
* ProcessRequest で通信リクエスト開始

![SimpleGet_02.jpg](/Examples/01_SimpleGet/SimpleGet_02.jpg)

### 結果

![SimpleGet_03.jpg](/Examples/01_SimpleGet/SimpleGet_03.jpg)

