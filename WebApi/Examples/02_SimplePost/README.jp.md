SimplePost
==================================

シンプルなPOST通信サンプルです。

## 手順

### 接続先を作成

サーバー上に info.php を配置します。

### Web API クラス定義

Blueprint で WebApi クラスを継承した BP_WebApiPost クラスを作成します。

ClassDefaults から接続先の Url を任意のものに変更します。

![SimplePost_01.jpg](/Examples/02_SimplePost/SimplePost_01.jpg)

ClassSettings から Interfaces に WebApiPreFilterInterface を追加します。

![SimplePost_05.jpg](/Examples/02_SimplePost/SimplePost_05.jpg)

ExecuteWebApiPreFilter に以下の処理を記述します。

1. CreateRequestBody を使用して WebApiRequestBodyJson のインスタンスを作成
* WebApiRequestBodyUrlParameter から WebApiRequestBodyJson に対して共通項目をコピー
* Return で返す時に WebApiRequestBody クラスを WebApiRequestBodyJson に変更

![SimplePost_02.jpg](/Examples/02_SimplePost/SimplePost_02.jpg)

### Web API 呼び出し

以下の画像を参考に Web API 呼び出しを記述します。

1. WebApi のインスタンスを作成
* リクエスト処理成功時イベント（OnRequestSuccessed）にイベントを追加
* OnRequestSuccessed 内で文字列形式レスポンス（WebApiResponseBodyString）へキャストし、レスポンスを出力
* ProcessRequest で通信リクエスト開始

![SimplePost_03.jpg](/Examples/02_SimplePost/SimplePost_03.jpg)

## 結果

![SimplePost_04.jpg](/Examples/02_SimplePost/SimplePost_04.jpg)
