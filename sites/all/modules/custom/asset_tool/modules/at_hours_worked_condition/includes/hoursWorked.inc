<?php

class hoursWorked extends assetToolConditionBase {
  static $machine_name = 'hours_worked';

  public static function settingsForm() {

    $settings = variable_get('app_system_hours_worked', array());

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
          ),
          'y' => array(
            '#type' => 'textfield',
            '#title' => t('y'),
            '#default_value' => isset($settings['scoring_profile']['min']['y'])? $settings['scoring_profile']['min']['y'] : NULL,
          ),
        ),
        'max' => array(
          '#type' => 'item',
          '#title' => t('Max'),
          'x' => array(
            '#type' => 'textfield',
            '#title' => t('x'),
            '#default_value' => isset($settings['scoring_profile']['max']['x'])? $settings['scoring_profile']['max']['x'] : NULL,
          ),
          'y' => array(
            '#type' => 'textfield',
            '#title' => t('y'),
            '#default_value' => isset($settings['scoring_profile']['max']['y'])? $settings['scoring_profile']['max']['y'] : NULL,
          ),
        )
      ),
    );

    return $form;
  }

  public static function settingsFormValidate($form, &$form_state) {

  }

  public static function settingsFormSubmit($form, &$form_state) {
    variable_set('app_system_hours_worked', $form_state['values']['hours_worked']);
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