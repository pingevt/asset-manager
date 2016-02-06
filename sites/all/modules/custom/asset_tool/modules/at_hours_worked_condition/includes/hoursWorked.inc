<?php

class hoursWorked extends assetToolConditionBase {
  static $machine_name = 'hours_worked';

  public static function settingsForm() {

    $settings = variable_get('app_system_' . self::$machine_name, array());

    if (!isset($settings['scoring_profile']['min']['x'])) {
      $settings['scoring_profile']['min']['x'] = 0;
    }
    if (!isset($settings['scoring_profile']['min']['y'])) {
      $settings['scoring_profile']['min']['y'] = 0;
    }
    if (!isset($settings['scoring_profile']['max']['x'])) {
      $settings['scoring_profile']['max']['x'] = 0;
    }
    if (!isset($settings['scoring_profile']['max']['y'])) {
      $settings['scoring_profile']['max']['y'] = 0;
    }

    $max_x = $settings['scoring_profile']['max']['x'];
    $max_y = $settings['scoring_profile']['max']['y'];
    $min_x = $settings['scoring_profile']['min']['x'];
    $min_y = $settings['scoring_profile']['min']['y'];

    $slope = ($max_y - $min_y) / ($max_x - $min_x);
    $b = $max_y - $slope * $max_x;

    $form = array(
      '#type' => 'fieldset',
      '#title' => t('Hours Worked Settings'),
      '#collapsible' => TRUE,
      'scoring_profile' => array(
        '#type' => 'item',
        '#title' => t('Scoring Profile'),
        'min' => array(
          '#type' => 'item',
          '#title' => t('Min'),
          'x' => array(
            '#type' => 'textfield',
            '#title' => t('x'),
            '#default_value' => isset($settings['scoring_profile']['min']['x'])? $settings['scoring_profile']['min']['x'] : NULL,
            '#size' => 10,
          ),
          'y' => array(
            '#type' => 'textfield',
            '#title' => t('y'),
            '#default_value' => isset($settings['scoring_profile']['min']['y'])? $settings['scoring_profile']['min']['y'] : NULL,
            '#size' => 10,
          ),
        ),
        'max' => array(
          '#type' => 'item',
          '#title' => t('Max'),
          'x' => array(
            '#type' => 'textfield',
            '#title' => t('x'),
            '#default_value' => isset($settings['scoring_profile']['max']['x'])? $settings['scoring_profile']['max']['x'] : NULL,
            '#size' => 10,
          ),
          'y' => array(
            '#type' => 'textfield',
            '#title' => t('y'),
            '#default_value' => isset($settings['scoring_profile']['max']['y'])? $settings['scoring_profile']['max']['y'] : NULL,
            '#size' => 10,
          ),
        ),
        'equation' => array(
          '#markup' => 'y = '.$slope.'x + '. $b,
        ),
        '#suffix' => '<div class="ct-chart-' . self::$machine_name . '"></div>
      <script>
var options = {
axisX: {
  type: Chartist.FixedScaleAxis,
  low: 0,
  high: 100,
  divisor: 4,
  ticks: [0, 25, 50, 75, 100]
},
axisY: {
  type: Chartist.FixedScaleAxis,
  low: 0,
  high: 100,
  divisor: 4,
  ticks: [0, 25, 50, 75, 100]
},
width: \'100%\',
height: \'200px\',
};
var data = {
  series: [
    [
      {x: ' . $settings['scoring_profile']['min']['x'] . ', y: ' . $settings['scoring_profile']['min']['y'] . '},
      {x: ' . $settings['scoring_profile']['max']['x'] . ', y:' . $settings['scoring_profile']['max']['y'] . '}
    ]
  ]
};
new Chartist.Line(\'.ct-chart-' . self::$machine_name . '\', data, options);
      </script>
        ',
      ),
    );

    return $form;
  }

  public static function settingsFormValidate($form, &$form_state) {

  }

  public static function settingsFormSubmit($form, &$form_state) {
    variable_set('app_system_' . self::$machine_name, $form_state['values'][self::$machine_name]);
  }

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