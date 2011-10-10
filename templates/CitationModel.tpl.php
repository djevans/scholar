<div id="overview">
  <div id="citation">
    <h3 style="display:inline">
      <?php print t('Citation:') ?>
    </h3> 
    <select class="form-select" onchange="">
      <option value="0">APA</option>
    </select>
    <?php print print_r($citation, TRUE); ?>
    <?php print drupal_get_form('islandora_bibliography_citation_form', $pid); ?>
  </div>
  <?php if (!empty($abstract)): ?>
    <div id="abstract">
      <h3><?php print t('Abstract:') ?></h3>
      <div id="abstract-content"><?php print print_r($abstract, TRUE); ?></div>
    </div>
  <?php endif; ?>
</div>