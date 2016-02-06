<?php

interface assetToolConditionBaseInterface {
  public static function assetFormItems($asset, $n);

  public static function hookSchema();

  public static function viewFullHeader(&$header);

  public static function viewFullRows(&$rows, $data);

  public static function isDataRecordEmpty($record);
}

class assetToolConditionBase implements assetToolConditionBaseInterface {
  static $machine_name = '';

   public static function assetFormItems($asset, $n) {
    $form = array();

    return $form;
  }

  public static function hookSchema() {
    return array();
  }

  public static function settingsForm($asset_type_id) {}
  public static function settingsFormValidate($form, &$form_state, $asset_type_id) {}
  public static function settingsFormSubmit($form, &$form_state, $asset_type_id) {}

  public static function viewFullHeader(&$header) {}

  public static function viewFullRows(&$rows, $data) {}

  public static function isDataRecordEmpty($record) {}
}