JsonResponse
==================================

JSONフォーマットでレスポンスを受け取った時に中身をパースするサンプルです。

## 手順

### 接続先を作成

サーバー上に json.php を配置します。

### Web API クラス定義

Blueprint で WebApi クラスを継承した BP_WebApiJson クラスを作成します。

ClassDefaults から接続先の Url を任意のものに変更します。

![JsonResponse_01.jpg](/Examples/03_JsonResponse/JsonResponse_01.jpg)

ClassSettings から Interfaces に WebApiPostFilterInterface を追加します。

![JsonResponse_02.jpg](/Examples/03_JsonResponse/JsonResponse_02.jpg)

ExecuteWebApiPostFilter に以下の処理を記述します。

1. CreateResponseBody を使用して WebApiResponseBodyJson のインスタンスを作成
* WebApiResponseBodyString から WebApiResponseBodyJson に対して共通項目をコピー
* Return で返す時に WebApiResponseBody クラスを WebApiResponseBodyJson に変更

![JsonResponse_03.jpg](/Examples/03_JsonResponse/JsonResponse_03.jpg)

### Web API 呼び出し

以下の画像を参考に Web API 呼び出しを記述します。

1. WebApi のインスタンスを作成
* リクエスト処理成功時イベント（OnRequestSuccessed）にイベントを追加
* OnRequestSuccessed 内で JSON 形式レスポンス（WebApiResponseBodyJson）へキャストし、レスポンスを出力
* 更に ParseInt 関数で JSON 文字列レスポンスに含まれる int レスポンス（int）をパースして出力
* 更に ParseObject 関数で JSON 文字列レスポンスに含まれる object レスポンス（object/foo）をパースして出力
* ProcessRequest で通信リクエスト開始

![JsonResponse_04.jpg](/Examples/03_JsonResponse/JsonResponse_04.jpg)

ParseInt 関数に int フィールドのパース処理を記述します。

![JsonResponse_05.jpg](/Examples/03_JsonResponse/JsonResponse_05.jpg)

ParseObject 関数に object フィールドのパース処理を記述します。

![JsonResponse_06.jpg](/Examples/03_JsonResponse/JsonResponse_06.jpg)

## 結果

![JsonResponse_07.jpg](/Examples/03_JsonResponse/JsonResponse_07.jpg)
