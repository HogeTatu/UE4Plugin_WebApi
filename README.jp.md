UE4Plugin_WebApi
==================================

UE4 で Web API （HTTP通信）を使用するためのプラグインです。

## コンセプト

* HTTPモジュールのラッパー
* API単位でクラス定義
* 通信前、通信後に実行する処理をAPI別に定義できるフィルタシステム

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
[詳細](/Examples/01_SimpleGet/SimpleGet.jp.md "SimpleGet.jp.md")
