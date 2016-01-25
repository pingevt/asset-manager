<?php

class hoursWorked extends assetToolConditionBase {
  static $machine_name = 'hours_worked';

  public static function assetFormItems($asset, $n) {
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => 'Hours worked',
      '#default_value' => isset($asset->data[$n][self::$machine_name . '_value'])? $asset->data[$n][self::$machine_name . '_value'] : '',
    );

    return $form;
  }

  public static function hookSchema() {
    return array(
      'fields' => array(
        'hours_worked_value' => array(
          'description' => 'The value.',
          'type' => 'int',
          'not null' => FALSE,
          'default' => NULL,
        ),
      ),
    );
  }

  public static function viewFullHeader(&$header) {
    $header[] = 'Hours Worked';
  }

  public static function viewFullRows(&$rows, $data) {
    foreach ($data as $n => $d) {
      $rows[$n][] = $d['hours_worked_value'];
    }
  }

  public static function isDataRecordEmpty($record) {
    if (!empty($record['hours_worked']['value'])) {
      return FALSE;
    }
  }
}