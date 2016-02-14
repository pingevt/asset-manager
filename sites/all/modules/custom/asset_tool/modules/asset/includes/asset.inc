<?php

class Asset extends Entity {

  public function label() {
    return empty($this->title) ? 'Untitled Asset' : $this->title;
  }

  public function runReport() {
    $app_system_period = variable_get('app_system_period', '');
    $periods_in_year = array(
      'monthly' => 12,
      'quarterly' => 4,
      'biannually' => 2,
      'annually' => 1,
    );

    $n = count($this->data);

    $first_year_period_count = $periods_in_year[$app_system_period] - ($this->start_period - 1);

    $ytd_periods = ($n - $first_year_period_count) % $periods_in_year[$app_system_period];

    if ($ytd_periods < 0) {
      $ytd_periods = $n;
    }
    $ytd_start_n = $n - $ytd_periods;

    $report = array();

    $target_age_settings = variable_get('app_target_age_settings', array());

    if ($n > 1) {
      $report = array(
        'n1_data' => array(
          'ytd' => array(
            'age' => $ytd_periods - 1,
          ),
          'ltd' => array(
            'age' => ($n - 1),
          ),
        ),
        'n_data' => array(
          'ytd' => array(
            'age' => $ytd_periods,
          ),
          'ltd' => array(
            'age' => $n,
          ),
        ),
        'ranking_metrics' => array(
          'period' => array(
            'age' => NULL,
          ),
          'ytd' => array(
            'age' => NULL,
          ),
          'ltd' => array(
            'age' => round(($n / $target_age_settings[$this->type]), 2),
          ),
        ),
        'ranking_metrics_scores' => array(
          'period' => array(
            'age' => NULL,
          ),
          'ytd' => array(
            'age' => NULL,
          ),
          'ltd' => array(
            'age' => round($this->getScore(($n / $target_age_settings[$this->type]), 0, 0, 0, 0), 2),
          ),
        ),
        'total_score' => NULL,
      );

      $conditions = asset_tool_conditions_load();
      foreach ($conditions as $condition_id => $condition) {
        $condition['controller']::runReport($report, $this, $this->data, $ytd_start_n);
      }
    }

    $coefficient_settings = variable_get('app_' . $this->type . '_coefficients', array());

    $total_score = 0;
    foreach ($report['ranking_metrics_scores'] as $timeframe => $tf_data) {
      foreach ($tf_data as $condition_id => $value) {
        $total_score += $coefficient_settings[$condition_id][$timeframe] * $value;
      }
    }
    $report['total_score'] = $total_score;

    $up = entity_get_controller($this->entityType)->saveReport($report, $this);
  }

  public static function getScore($value, $x_min, $x_max, $y_min, $y_max) {
    if ($value > $x_max) {
      return $y_max;
    }
    elseif ($value < $x_min) {
      return $y_min;
    }
    else {
      $slope = (($x_max - $x_min) == 0)? '0' : ($y_max - $y_min) / ($x_max - $x_min);
      $b = $y_max - $slope * $x_max;

      return $value * $slope + $b;
    }
  }
}

class AssetController extends EntityAPIController {

  /**
   * override create().
   */
  public function create(array $values = array()) {
    $values['data'] = array();
    return parent::create($values);
  }

  /**
   * override load().
   */
  public function load($ids = array(), $conditions = array()) {
    $entities = parent::load($ids, $conditions);

    // Load data
    foreach ($entities as &$entity) {
      /*
      if(is_string($entity->report_data)) {
        $entity->report_data = unserialize($entity->report_data);
      }
      */

      $entity->data = array();

      $q = db_select('asset_data', 'ad');
      $q->fields('ad');
      $q->condition('ad.aid', $entity->aid);
      $q->orderBy('n', 'ASC');
      $results = $q->execute();

      while ($row = $results->fetchAssoc()) {
        $entity->data[$row['n']] = $row;
      }
    }

    return $entities;
  }

  /**
   * Override the save method.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (isset($entity->is_new)) {
      $entity->created = REQUEST_TIME;

      global $user;
      $entity->uid = $user->uid;
    }

    if (isset($entity->description_field)) {
      $entity->description = $entity->description_field['value'];
      $entity->description_format = $entity->description_field['format'];
    }

    $entity->changed = REQUEST_TIME;

    $return = parent::save($entity, $transaction);

    // Save/Update data
    foreach ($entity->data as $n => $r) {
      if (!$this->isDataRecordEmpty($r)) {
        // Save data record.
        $data = array();
        if (isset($r['adid'])) {
          $data['adid'] = $r['adid'];
        }
        $data += array(
          'aid' => $entity->aid,
          'n' => $n
        );

        foreach ($r as $mod => $vals) {
          if ($mod != 'adid' && $mod != 'delete' ) {
            foreach ($vals as $field => $val) {
              $data[$mod . '_' . $field] = $val;
            }
          }
        }

        if (isset($data['adid'])) {
          if ($t = drupal_write_record('asset_data', $data, array('adid'))) {
            drupal_set_message($t . ' data', 'notice');
          }
          else {
            drupal_set_message('Did not save data', 'error');
          }
        }
        else {
          if ($t = drupal_write_record('asset_data', $data)) {
            drupal_set_message($t . ' data', 'notice');
          }
          else {
            drupal_set_message('Did not save data', 'error');
          }
        }
      }
    }

    return $return;
  }

  private function isDataRecordEmpty($r) {
    $conditions = asset_tool_conditions_load();

    $empty = TRUE;

    foreach ($conditions as $condition) {
      if ($condition['controller']::isDataRecordEmpty($r) === FALSE) {
        $empty = FALSE;
      }
    }

    return $empty;
  }

  public function saveReport($report, $asset) {
    $data = serialize($report);

    $num_updated = db_update('asset')
      ->fields(array(
        'report_data' => $data,
      ))
      ->condition('aid', $asset->aid)
      ->execute();
    return $num_updated;
  }
}

/**
 * Custom controller for the administrator UI.
 */
class AssetUIController extends EntityDefaultUIController {

  /**
   * Override the menu hook for default ui controller.
   */
  public function hook_menu() {
    $items = parent::hook_menu();

    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';

    $items[$this->path]['title'] = t('Asset');
    $items[$this->path]['description'] = t('Manage Assets, including fields.');
    $items[$this->path]['access callback'] = 'asset_access_callback';
    $items[$this->path]['access arguments'] = array('administer asset entities');
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    $items['asset/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      //'title callback' => 'entity_label',
      //'title arguments' => array($this->entityType, 1),
      'page callback' => 'entity_ui_get_form',
      'page arguments' => array($this->entityType, 1),
      'load arguments' => array($this->entityType),
      'access callback' => 'entity_access',
      'access arguments' => array('update', $this->entityType, 1),
      'file' => 'asset.admin.inc',
      'file path' => drupal_get_path('module', 'asset') . '/includes',
      'type' => MENU_LOCAL_TASK,
      'weight' => 1,
    );

    $items['asset/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'drupal_get_form',
      'page arguments' => array($this->entityType . '_operation_form', $this->entityType, 1, 2),
      'load arguments' => array($this->entityType),
      'access callback' => 'entity_access',
      'access arguments' => array('delete', $this->entityType, 1),
      'file' => 'asset.admin.inc',
      'file path' => drupal_get_path('module', 'asset') . '/includes',
      'type' => MENU_LOCAL_TASK,
      'weight' => 2,
    );

    return $items;
  }

  /**
   * Admin form for searching and doing bulk operations.
   */
  public function overviewForm($form, &$form_state) {
    return parent::overviewForm($form, $form_state);
  }

  /**
   * Form Submit method.
   */
  public function overviewFormSubmit($form, &$form_state) {
    return parent::overviewFormSubmit($form, $form_state);
  }


  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $entity_uri = entity_uri($this->entityType, $entity);

    $row[] = array('data' => array(
      '#theme' => 'entity_ui_overview_item',
      '#label' => entity_label($this->entityType, $entity),
      '#name' => !empty($this->entityInfo['exportable']) ? entity_id($this->entityType, $entity) : FALSE,
      '#url' => $entity_uri ? $entity_uri : FALSE,
      '#entity_type' => $this->entityType),
    );

    // Add in any passed additional cols.
    foreach ($additional_cols as $col) {
      $row[] = $col;
    }

    // Add a row for the exportable status.
    if (!empty($this->entityInfo['exportable'])) {
      $row[] = array('data' => array(
        '#theme' => 'entity_status',
        '#status' => $entity->{$this->statusKey},
      ));
    }
    // In case this is a bundle, we add links to the field ui tabs.
    $field_ui = !empty($this->entityInfo['bundle of']) && entity_type_is_fieldable($this->entityInfo['bundle of']) && module_exists('field_ui');
    // For exportable entities we add an export link.
    $exportable = !empty($this->entityInfo['exportable']);
    // If i18n integration is enabled, add a link to the translate tab.
    $i18n = !empty($this->entityInfo['i18n controller class']);

    // Add operations depending on the status.
    if (entity_has_status($this->entityType, $entity, ENTITY_FIXED)) {
      $row[] = array('data' => l(t('clone'), $this->path . '/manage/' . $id . '/clone'), 'colspan' => $this->operationCount());
    }
    else {
      $row[] = l(t('edit'), $this->path . '/manage/' . $id);

      if ($field_ui) {
        $row[] = l(t('manage fields'), $this->path . '/manage/' . $id . '/fields');
        $row[] = l(t('manage display'), $this->path . '/manage/' . $id . '/display');
      }
      if ($i18n) {
        $row[] = l(t('translate'), $this->path . '/manage/' . $id . '/translate');
      }
      if ($exportable) {
        $row[] = l(t('clone'), $this->path . '/manage/' . $id . '/clone');
      }

      if (empty($this->entityInfo['exportable']) || !entity_has_status($this->entityType, $entity, ENTITY_IN_CODE)) {
        $row[] = l(t('delete'), $this->path . '/manage/' . $id . '/delete', array('query' => drupal_get_destination()));
      }
      elseif (entity_has_status($this->entityType, $entity, ENTITY_OVERRIDDEN)) {
        $row[] = l(t('revert'), $this->path . '/manage/' . $id . '/revert', array('query' => drupal_get_destination()));
      }
      else {
        $row[] = '';
      }
    }
    if ($exportable) {
      $row[] = l(t('export'), $this->path . '/manage/' . $id . '/export');
    }
    return $row;
  }
}