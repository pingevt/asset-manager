<?php

class hoursDowned extends assetToolConditionBase {
  static $machine_name = 'hours_downed';

  public static function settingsForm($asset_type_id) {
    $settings = variable_get('app_system_' . $asset_type_id . '_' . self::$machine_name, array());

    if (!isset($settings['scoring_profile']['min']['x'])) {
      $settings['scoring_profile']['min']['x'] = 20;
    }
    if (!isset($settings['scoring_profile']['min']['y'])) {
      $settings['scoring_profile']['min']['y'] = 0;
    }
    if (!isset($settings['scoring_profile']['max']['x'])) {
      $settings['scoring_profile']['max']['x'] = 100;
    }
    if (!isset($settings['scoring_profile']['max']['y'])) {
      $settings['scoring_profile']['max']['y'] = 100;
    }

    $max_x = $settings['scoring_profile']['max']['x'];
    $max_y = $settings['scoring_profile']['max']['y'];
    $min_x = $settings['scoring_profile']['min']['x'];
    $min_y = $settings['scoring_profile']['min']['y'];

    $slope = (($max_x - $min_x) == 0)? '0' : ($max_y - $min_y) / ($max_x - $min_x);
    $b = $max_y - $slope * $max_x;

    $form = array(
      '#type' => 'fieldset',
      '#title' => t('Hours Down Settings'),
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
          '#markup' => 'y = ' . $slope . 'x + ' . $b,
        ),
        '#suffix' => '<div class="ct-chart-' . self::$machine_name . '-' . $asset_type_id . '"></div>
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
new Chartist.Line(\'.ct-chart-' . self::$machine_name . '-' . $asset_type_id . '\', data, options);
      </script>
        ',
      ),
    );

    return $form;
  }

  public static function settingsFormValidate($form, &$form_state, $asset_type_id) {

  }

  public static function settingsFormSubmit($form, &$form_state, $asset_type_id) {
    variable_set('app_system_' . $asset_type_id . '_' . self::$machine_name, $form_state['values'][$asset_type_id][self::$machine_name]);
  }

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

  public static function isDataRecordEmpty($record) {
    if (!empty($record['hours_downed']['value'])) {
      return FALSE;
    }
  }

  public static function reportTableHeaderRow(&$column_headers, $num_of_columns_section, $delta) {
    $column_headers[$num_of_columns_section * 0 + $delta] = 'Hours Down';
    $column_headers[$num_of_columns_section * 1 + $delta] = 'Hours Down';
    $column_headers[$num_of_columns_section * 2 + $delta] = 'Hours Down';
    $column_headers[$num_of_columns_section * 3 + $delta] = 'Hours Down';
    $column_headers[$num_of_columns_section * 4 + $delta] = 'Down Ratio';
    $column_headers[$num_of_columns_section * 5 + $delta] = 'Down Ratio';
    $column_headers[$num_of_columns_section * 6 + $delta] = 'Down Ratio';
    $column_headers[$num_of_columns_section * 7 + $delta] = 'Down Ratio';
    $column_headers[$num_of_columns_section * 8 + $delta] = 'Down Ratio';
    $column_headers[$num_of_columns_section * 9 + $delta] = 'Down Ratio';
  }

  public static function runReport(&$report, $asset, $data, $ytd_start_n) {
    $settings = variable_get('app_system_' . $asset->type . '_' . self::$machine_name, array());

    $n_last = count($data) - 1;

    $n1_values_ytd = 0;
    $n1_values_ltd = 0;

    for ($i=0; $i<$n_last; $i++) {
      $n1_values_ltd += $data[$i][self::$machine_name . '_value'];
      if ($i >= $ytd_start_n) {
        $n1_values_ytd += $data[$i][self::$machine_name . '_value'];
      }
    }

    $n_values_ytd = ($n1_values_ytd + $data[$n_last][self::$machine_name . '_value']);
    $n_values_ltd = ($n1_values_ltd + $data[$n_last][self::$machine_name . '_value']);

    $ranking_metrics_period = $data[$n_last][self::$machine_name . '_value'] / $data[$n_last]['hours_worked_value'];

    $ranking_metrics_ytd = $n_values_ytd / $report['n_data']['ytd']['hours_worked'];
    $ranking_metrics_ltd = $n_values_ltd / $report['n_data']['ltd']['hours_worked'];


    $report['n1_data']['ytd'][self::$machine_name] = $n1_values_ytd;
    $report['n1_data']['ltd'][self::$machine_name] = $n1_values_ltd;
    $report['n_data']['ytd'][self::$machine_name] = $n_values_ytd;
    $report['n_data']['ltd'][self::$machine_name] = $n_values_ltd;
    $report['ranking_metrics']['period'][self::$machine_name] = round($ranking_metrics_period, 2);
    $report['ranking_metrics']['ytd'][self::$machine_name] = round($ranking_metrics_ytd, 2);
    $report['ranking_metrics']['ltd'][self::$machine_name] = round($ranking_metrics_ltd, 2);
    $report['ranking_metrics_scores']['period'][self::$machine_name] = NULL;
    $report['ranking_metrics_scores']['ytd'][self::$machine_name] = Asset::getScore($ranking_metrics_ytd, $settings['scoring_profile']['min']['x'], $settings['scoring_profile']['max']['x'], $settings['scoring_profile']['min']['y'], $settings['scoring_profile']['max']['y']);
    $report['ranking_metrics_scores']['ltd'][self::$machine_name] = Asset::getScore($ranking_metrics_ltd, $settings['scoring_profile']['min']['x'], $settings['scoring_profile']['max']['x'], $settings['scoring_profile']['min']['y'], $settings['scoring_profile']['max']['y']);

  }
}