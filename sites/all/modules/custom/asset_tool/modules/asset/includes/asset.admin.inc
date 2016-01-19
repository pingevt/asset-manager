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
dpm($asset);
  $form['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#default_value' => isset($asset->name) ? $asset->name : '',
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

  field_attach_form('asset', $asset, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => isset($asset->aid) ? t('Update Asset') : t('Save Asset'),
    ),
    'delete_link' => array(
      '#markup' => isset($asset->aid) ? l(t('Delete'),'admin/content/asset/manage/' . $asset->aid . '/delete', array('attributes' => array('id' => array('asset-delete-' . $asset->aid), 'class' => array('button remove')), 'query' => array('destination' => 'admin/content/assets'))) : '',
    )
  );

  return $form;
}

/**
 * Implements hook_form_validate().
 */
function asset_form_validate($form, &$form_state) {

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