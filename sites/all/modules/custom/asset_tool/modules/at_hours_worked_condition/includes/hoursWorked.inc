<?php

class hoursWorked extends assetToolConditionBase {
  static $machine_name = 'hours_worked';

  public static function assetFormItems($asset, $n) {
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => 'Hours worked',
      '#default_value' => isset($asset->reports[$n][self::$machine_name]['value'])? $asset->reports[$n][self::$machine_name]['value'] : '',
    );

    return $form;
  }

  public static function saveReports($asset, $n) {
    $item = array(
      'aid' => $asset->aid,
      'n' => $n,
      'value' => $asset->reports[$n][self::$machine_name]['value'],
    );

    return drupal_write_record('atc_hours_worked', $item, array('aid', 'n'));
  }
}