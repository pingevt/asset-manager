<?php

class hoursDowned extends assetToolConditionBase {
  static $machine_name = 'hours_downed';

  public static function assetFormItems($asset, $n) {
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => 'Hours down',
      '#default_value' => isset($asset->data[$n][self::$machine_name . '_value'])? $asset->data[$n][self::$machine_name . '_value'] : '',
    );

    return $form;
  }

  public static function hookSchema() {
    return array(
      'fields' => array(
        'hours_downed_value' => array(
          'description' => 'The value.',
          'type' => 'int',
          'not null' => FALSE,
          'default' => NULL,
        ),
      ),
    );
  }

  public static function viewFullHeader(&$header) {
    $header[] = 'Hours Downed';
  }

  public static function viewFullRows(&$rows, $data) {
    foreach ($data as $n => $d) {
      $rows[$n][] = $d['hours_downed_value'];
    }
  }
}