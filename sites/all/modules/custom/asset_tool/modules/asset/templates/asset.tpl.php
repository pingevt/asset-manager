<?php
//dpm($content);
?>
<div id="asset-<?php print $asset->aid; ?>" class="<?php print $classes; ?> clearfix" <?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $asset_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <div class="row">

    <div class="col-sm-6">
      <div class="block">
        <div class="block-header bg-primary"></div>
        <div class="block-content">
          <div class="form-group">
            <label>Type:</label>
            <div><?php print $asset->type; ?></div>
          </div>

          <div class="form-group">
            <label>Starting Year:</label>
            <div><?php print $asset->start_period_year; ?></div>
          </div>

          <div class="form-group">
            <label>Starting Period:</label>
            <div><?php print $asset->start_period; ?></div>
          </div>
        </div>
      </div>
    </div>

    <div class="col-sm-6">
      <div class="block">
        <div class="block-header bg-primary">
        </div>
        <div class="block-content">
          <div class="form-group">
            <label>External ID:</label>
            <div><?php print $asset->external_id; ?></div>
          </div>
          <div class="form-group">
            <label>Description:</label>
            <div><?php print check_markup($asset->description, $asset->description_format); ?></div>
          </div>
        </div>
      </div>
    </div>
  </div>

  <div class="row">
    <div class="col-sm-12">
      <div class="block block-themed">
        <!--
        <div class="block-header bg-primary">
          <h3 class="block-title">Data</h3>
        </div>
        -->

        <ul class="nav nav-tabs" data-toggle="tabs">
            <li class="active">
                <a href="#asset-data">Data</a>
            </li>
            <li class="">
               <a href="#asset-data-form"><i class="si si-plus"></i></a>
            </li>
        </ul>
        <div class="block-content tab-content">
          <div id="asset-data" class="tab-pane active">
            <?php print render($content['data']); ?>
          </div>
          <div id="asset-data-form" class="tab-pane">
            <?php print render($content['data_form']); ?>
          </div>
        </div>
      </div>
    </div>
  </div>

  <div class="row">
    <div class="col-sm-12">
      <div class="block block-themed">
        <div class="block-header bg-primary-light">
          <div class="block-options-simple">
            <a href="/asset/<?php print $asset->aid; ?>/clear-report" class="btn btn-sm btn-warning" type="submit"><i class="fa fa-eraser"></i> Clear Report</a>
            <a href="/asset/<?php print $asset->aid; ?>/run-report" class="btn btn-sm btn-success" type="submit"><i class="fa fa-calculator"></i> Run Report</a>
          </div>
          <h3 class="block-title">Reports</h3>
        </div>
        <div class="block-content">
          <?php print render($report); ?>
        </div>
      </div>
    </div>

  </div>
</div>
