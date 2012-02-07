<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:mods="http://www.loc.gov/mods/v3" version="1.0">
  <xsl:param name="referer"/>
  <xsl:output method="text"/>
  <xsl:strip-space elements="*"/>
  <xsl:template match="/">
    <xsl:text>ctx_ver=Z39.88-2004</xsl:text>
    <xsl:text>&amp;</xsl:text>
    <xsl:text>rft_val_fmt=info%3Aofi%2Ffmt%3Akev%3Amtx%3Ajournal</xsl:text>
    <xsl:text>&amp;</xsl:text>
    <xsl:text>rfr_id=</xsl:text>
    <xsl:value-of select="$referer"/>
    <!-- article title -->
    <xsl:apply-templates select="mods:mods/mods:titleInfo/mods:title" mode="article"/>
    <!-- ISSN -->
    <xsl:apply-templates select="mods:mods/mods:identifier[@type='issn']"/>
    <!-- eISSN -->
    <xsl:apply-templates select="mods:mods/mods:identifier[@type='eissn']"/>
    <!-- doi -->
    <xsl:apply-templates select="mods:mods/mods:identifier[@type='doi']"/>
    <!-- date created -->
    <!-- volume, issue -->
    <xsl:apply-templates select="mods:mods/mods:part/mods:detail"/>
    <!-- author(s) -->
    <xsl:apply-templates select="mods:mods/mods:name[mods:role/mods:roleTerm[@type='text' and text()='author']]"/>
    <xsl:apply-templates select="mods:mods/mods:name[mods:role/mods:roleTerm[@type='code' and text()='aut']]"/>
    <!-- start,end, total pages -->
    <xsl:apply-templates select="mods:mods/mods:part/mods:extent[@unit='page']"/>
    <!-- publisher -->
    <!-- journal title -->
    <!-- place of publication -->
    <xsl:apply-templates select="mods:mods/mods:relatedItem[@type='host']"/>
  </xsl:template>
  <xsl:template match="mods:title" mode="article">
    <xsl:if test="normalize-space()">
      <xsl:text>&amp;rft.atitle=</xsl:text>
      <xsl:value-of select="normalize-space()"/>
    </xsl:if>
  </xsl:template>
  <xsl:template match="mods:identifier">
    <xsl:if test="normalize-space()">
      <xsl:text>&amp;rft.</xsl:text>
      <xsl:value-of select="@type"/>
      <xsl:text>=</xsl:text>
      <xsl:value-of select="normalize-space()"/>
    </xsl:if>
  </xsl:template>
  <!-- volume, issue numbers -->
  <xsl:template match="mods:detail">
    <xsl:if test="mods:number[normalize-space()]">
      <xsl:text>&amp;rft.</xsl:text>
      <xsl:value-of select="@type"/>
      <xsl:text>=</xsl:text>
      <xsl:value-of select="mods:number"/>
    </xsl:if>
  </xsl:template>
  <xsl:template match="mods:name">
    <xsl:apply-templates select="mods:namePart"/>
  </xsl:template>
  <xsl:template match="mods:namePart">
    <xsl:if test="normalize-space()">
      <xsl:choose>
        <xsl:when test="@type">
          <xsl:choose>
            <xsl:when test="@type='family'">
              <xsl:text>&amp;rft.aulast=</xsl:text>
              <xsl:value-of select="normalize-space()"/>
            </xsl:when>
            <xsl:when test="@type='given'">
              <xsl:text>&amp;rft.aufirst=</xsl:text>
              <xsl:value-of select="normalize-space()"/>
            </xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:otherwise>
          <xsl:text>&amp;rft.au=</xsl:text>
          <xsl:value-of select="normalize-space()"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>
  </xsl:template>
  <xsl:template match="mods:extent">
    <xsl:apply-templates select="mods:start" mode="pages"/>
    <xsl:apply-templates select="mods:end" mode="pages"/>
    <xsl:apply-templates select="mods:total" mode="pages"/>
  </xsl:template>
  <xsl:template match="node()" mode="pages">
    <xsl:if test="normalize-space()">
      <xsl:text>&amp;rft.</xsl:text>
      <xsl:value-of select="local-name()"/>
      <xsl:text>=</xsl:text>
      <xsl:value-of select="normalize-space()"/>
    </xsl:if>
  </xsl:template>
  <xsl:template match="mods:relatedItem">
    <xsl:apply-templates select="mods:titleInfo/mods:title" mode="publisher"/>
    <xsl:apply-templates select="mods:originInfo/mods:publisher"/>
  </xsl:template>
  <xsl:template match="mods:title" mode="publisher">
    <xsl:if test="normalize-space()">
      <xsl:text>&amp;rft.jtitle=</xsl:text>
      <xsl:value-of select="normalize-space()"/>
    </xsl:if>
  </xsl:template>
  <xsl:template match="mods:publisher">
    <xsl:if test="normalize-space()">
      <xsl:text>&amp;rft.pub=</xsl:text>
      <xsl:value-of select="normalize-space()"/>
    </xsl:if>
  </xsl:template>
</xsl:stylesheet>
