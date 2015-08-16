UE4Plugin_WebApi
==================================

UE4 で Web API （HTTP通信）を使用するためのプラグインです。

## コンセプト

* HTTPモジュールのラッパー
* API単位でクラス定義
* 通信前、進捗、成功時、失敗時、完了時イベントの追加
* 通信前、通信後に実行する処理をAPI別に定義できるフィルタ機能

## フィルタ機能とは

フィルタ機能はAPI単位での処理を記述するためのものです。  
これにより様々な Web API で使用できる様な汎用的な作りとなっています。

### 通信前フィルタでできること

* 通信タイプ（GET、POST、PUT）を変更
* リクエストパラメータの追加/削除
* リクエストパラメータのフォーマット（JSON、MessagePack等）を変更

### 通信後フィルタでできること

* レスポンスコードの変更
* レスポンスのフォーマット（JSON、MessagePack等）を変更
* レスポンスに対する独自パース処理の記述

## 使い方

リポジトリをクローンもしくはZIPをダウンロードした後、プロジェクトのプラグインディレクトリに配置します。

```
[プロジェクト名]/Plugins/WebApi
```

VisualStudioでビルド後、プラグインのコンフィギュレーションからプラグインを有効にして下さい。

```
Project -> Networking -> WebApi
```

## サンプル動画

![ExampleMovie.gif](/Examples/ExampleMovie.gif)

## 機能サンプル

### SimpleGet

シンプルなGET通信サンプルです。  
[詳細](/Examples/01_SimpleGet/README.jp.md "README.jp.md")

### SimplePost

シンプルなPOST通信サンプルです。  
[詳細](/Examples/02_SimplePost/README.jp.md "README.jp.md")

### JsonResponse

JSONフォーマットでレスポンスを受け取った時に中身をパースするサンプルです。  
[詳細](/Examples/03_JsonResponse/README.jp.md "README.jp.md")
