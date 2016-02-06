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

  public static function settingsFormSubmit($form, &$form_state) {
    variable_set('app_system_' . self::$machine_name, $form_state['values'][self::$machine_name]);
  }

  public static function viewFullHeader(&$header) {}

  public static function viewFullRows(&$rows, $data) {}

  public static function isDataRecordEmpty($record) {}
}