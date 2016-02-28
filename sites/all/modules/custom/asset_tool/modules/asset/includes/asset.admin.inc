<?php
/**
 * @file
 * The file for admin forms and functionality for the asset entity
 */

/**
 * Implements hook_form().
 */
function asset_form($form, &$form_state, $asset = NULL) {
  $form = array();
  $settings = variable_get('app_system_period', '');

  if ($settings != '') {
    $form['name'] = array(
      '#title' => t('Name'),
      '#type' => 'textfield',
      '#default_value' => isset($asset->name) ? $asset->name : '',
      '#required' => TRUE,
      '#maxlength' => 255,
    );

    $form['external_id'] = array(
      '#title' => t('External ID'),
      '#type' => 'textfield',
      '#default_value' => isset($asset->external_id) ? $asset->external_id : '',
      '#required' => TRUE,
      '#maxlength' => 255,
    );

    $types = array('' => 'Select') + asset_types_get();
    $form['type'] = array(
      '#title' => t('Type'),
      '#type' => 'select',
      '#options' => $types,
      '#default_value' => isset($asset->type) ? $asset->type : '',
      '#required' => TRUE,
      '#maxlength' => 255,
    );

    $form['description_field'] = array(
      '#type' => 'text_format',
      '#title' => t('Description'),
      '#default_value' => isset($asset->description) ? $asset->description : '',
      '#format' => isset($asset->description_format) ? $asset->description_format : 'plain_text',
    );

    $years = array('' => '--Select--');
    for ($i = (date('Y') -10); $i <= (date('Y') +2); $i++) {
      $years[$i] = $i;
    }
    $form['start_period_year'] = array(
      '#type' => 'select',
      '#title' => t('Starting Year'),
      '#options' => $years,
      '#default_value' => isset($asset->start_period_year) ? $asset->start_period_year : '',
      '#required' => TRUE,
    );

    $periods = array('' => '--Select--');
    switch ($settings) {
    case 'monthly':
      for ($i=1;$i<=12;$i++) {
        $periods[$i] = date('M', mktime(0, 0, 0, $i));
      }
      break;
    case 'quarterly':
      $periods += array(
        '1' => 'First Q',
        '2' => 'Second Q',
        '3' => 'Third Q',
        '4' => 'First Qourth',
      );
      break;
    case 'biannually':
      $periods += array(
        '1' => 'First Half',
        '2' => 'Second Half',
      );
      break;
    case 'annually':
      break;
    }

    if ($settings != 'annually') {
      $form['start_period'] = array(
        '#type' => 'select',
        '#title' => t('Starting Period'),
        '#options' => $periods,
        '#default_value' => isset($asset->start_period) ? $asset->start_period : '',
        '#required' => TRUE,
      );
    }
    else {
      $form['start_period'] = array(
        '#type' => 'hidden',
        '#value' => '0',
      );
    }

    field_attach_form('asset', $asset, $form, $form_state);

    $data_count = count($asset->data) + 1;
    $form['data'] = array(
      '#type' => 'fieldset',
      '#title' => t('title'),
      '#tree' => TRUE,
    );

    $conditions = asset_tool_conditions_load();

    for ($i=0; $i<$data_count; $i++) {
      $form['data'][$i] = array(
        '#type' => 'fieldset',
        '#title' => 'n = ' . ($i + 1),
      );

      if (isset($asset->data[$i]['adid'])) {
        $form['data'][$i]['adid'] = array(
          '#type' => 'hidden',
          '#value' => $asset->data[$i]['adid'],
        );
      }

      foreach ($conditions as $con_id => $cond) {
        $form['data'][$i][$con_id] = $cond['controller']::assetFormItems($asset, $i);
      }

      if ($i == ($data_count - 2)) {
        $form['data'][$i]['delete'] = array(
          '#type' => 'submit',
          '#value' => 'Remove',
          '#submit' => array('asset_form_delete_data'),
          '#attributes' => array(
            'class' => array('btn', 'btn-danger'),
          ),
        );
      }
    }

    $form['actions'] = array(
      '#type' => 'actions',
      'submit' => array(
        '#type' => 'submit',
        '#value' => isset($asset->aid) ? t('Update Asset') : t('Save Asset'),
        '#attributes' => array(
          'class' => array('btn', 'btn-success'),
        ),
      ),
      'delete_link' => array(
        '#markup' => isset($asset->aid) ? l(t('Delete'),'admin/content/asset/manage/' . $asset->aid . '/delete', array('attributes' => array('id' => array('asset-delete-' . $asset->aid), 'class' => array('button remove btn btn-danger')), 'query' => array('destination' => 'admin/content/assets'))) : '',
      )
    );
  }
  else {
    $form['text'] = array(
      '#markup' => t('App settings need to be set before creating Assets'),
    );
  }

  return $form;
}

/**
 * Implements hook_form_validate().
 */
function asset_form_validate($form, &$form_state) {
  // Validate external ID.
  $external_id_tmp = $form_state['values']['external_id'];

  $q = db_select('asset', 'a');
  $q->fields('a');
  $q->condition('external_id', $external_id_tmp);

  if (isset($form_state['asset']->aid)) {
    $q->condition('aid', $form_state['asset']->aid, '!=');
  }

  $result = $q->execute()->fetchAll();

  if (count($result) > 0) {
    form_set_error('external_id', 'This ID has already been used');
  }
}

/**
 * Implements hook_form_submit().
 */
function asset_form_submit($form, &$form_state) {
  $asset = entity_ui_form_submit_build_entity($form, $form_state);
  $asset->save();
  drupal_set_message(t('@name has been saved.', array('@name' => $asset->name)));
  // $form_state['redirect'] = 'admin/content/asset';
  $form_state['redirect'] = 'asset/' . $asset->aid;
}

function asset_form_delete_data($form, &$form_state) {
  $record_n = $form_state['triggering_element']['#array_parents'][1];
  $asset_id = $form_state['asset']->aid;

  $num_deleted = db_delete('asset_data')
    ->condition('aid', $asset_id)
    ->condition('n', $record_n)
    ->execute();
}

/**
 * Confirmation before bulk deleting assets.
 */
function asset_bulk_delete($form, &$form_state, $asset_ids) {
  $asset_ids = explode('|', $asset_ids);
  $assets = asset_load_multiple($asset_ids);
  $form = array();
  $form_state['asset_ids'] = $asset_ids;
  $variables = array(
    'type' => 'ul',
    'items' => array(),
    'title' => '',
    'attributes' => array(),
  );
  foreach ($assets as $asset) {
    $variables['items'][] = $asset->name;
  }
  $form['summary'] = array(
    '#markup' => theme_item_list($variables),
  );
  return confirm_form($form, t('Delete all assets?'), 'admin/content/asset', t('Placeholder description'), t('Delete all'), t('Cancel'));
}

/**
 * Implements hook_submit().
 */
function asset_bulk_delete_submit($form, &$form_state) {
  $asset_ids = $form_state['asset_ids'];
  asset_delete_multiple($asset_ids);
  drupal_set_message(t('assets deleted'));
  drupal_goto('admin/content/asset');
}


