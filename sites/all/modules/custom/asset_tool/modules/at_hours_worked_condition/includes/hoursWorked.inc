<?php

class hoursWorked extends assetToolConditionBase {
  static $machine_name = 'hours_worked';

  public static function assetFormItems($asset, $n) {
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => 'Hours worked',
      '#default_value' => isset($asset->reports[$n][self::$machine_name . '_value'])? $asset->reports[$n][self::$machine_name . '_value'] : '',
    );

    return $form;
  }

  public static function hookSchema() {
    return array(
      'fields' => array(
        'hours_worked_value' => array(
          'description' => 'The value.',
          'type' => 'int',
          'not null' => TRUE,
          'default' => 0,
        ),
      ),
    );
  }

  public static function viewFullHeader(&$header) {
    $header[] = 'Hours Worked';
  }

  public static function viewFullRows(&$rows, $reports) {
    foreach ($reports as $n => $report) {
      $rows[$n][] = $report['hours_worked_value'];
    }
  }
}