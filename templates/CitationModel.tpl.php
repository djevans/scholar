<div id="overview">
  <div id="citation">
    <h3><?php print t('Citation:') ?></h3>
    <?php print print_r($citation, TRUE); ?>
  </div>
  <?php if (isset($abstract)): ?>
    <div id="abstract">
      <h3><?php print t('Abstract:') ?></h3>
      <?php print print_r($abstract, TRUE); ?>
    </div>
  <?php endif; ?>
</div>