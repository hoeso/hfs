<?php
/************ Input *********************************************************
 * $SELECTRE1 :	    die ID des aus der 1. RE-Liste gewaehlten Eintrags.
 * $SELECTEM1 :	    die ID des aus der 1. EM-Liste gewaehlten Eintrags.
 * $SELECTMM1 :	    die ID des aus der 1. MM-Liste gewaehlten Eintrags.
 *		    Auf diese Werte sollen die Listen beim Zurueckspringen
 *		    wieder gesetzt werden.
 *****************************************************************************/
if( isset($_COOKIE["dahinNachSpeichern"]) )
{
  $dahin=$_COOKIE["dahinNachSpeichern"];
}

if( !isset( $dahin ) )
  $dahin="index.php?navi=CFS";//mit Fragezeichen evtl. &-Anhaengsel eroeffnen. Ein beginnendes & wuerde zum Dateinamen gerechnet werden


if( isset($dahin) and $dahin )
{
  $dahin=str_replace( "\\", "", $dahin );
  $dahin=str_replace( "'", "%27", $dahin );

  $dahin=str_replace( " ", "%20", $dahin );

  if( isset($TabelleSL1) )
    $dahin .= "&TabelleSL1=$TabelleSL1";
  if( isset($backupSELECTSL1) and $backupSELECTSL1 )
    $dahin .= "&SELECTSL1=$backupSELECTSL1";
  if( isset($SELECTSL1) )
  {
    $erg = strstr( $dahin, "SELECTSL1" );
    if( $erg )
    {   // alten Wert abhaengen und durch neuen ersetzen
      $arr = explode( "SELECTSL1", $dahin );
      $dahin = $arr[0] . "SELECTSL1=$SELECTSL1";
    }
    else	// kein alter Wert, also direkt anhaengen
      $dahin .= "&SELECTSL1=$SELECTSL1";
  }
  if( isset($SELECTEM1) )
  {
    $erg = strstr( $dahin, "SELECTEM1" );
    if( $erg )
    {   // alten Wert abhaengen und durch neuen ersetzen
      $arr = explode( "SELECTEM1", $dahin );
      $dahin = $arr[0] . "SELECTEM1=$SELECTEM1";
    }
    else	// kein alter Wert, also direkt anhaengen
      $dahin .= "&SELECTEM1=$SELECTEM1";
  }
  if( isset($SELECTRE1) )
  {
    $erg = strstr( $dahin, "SELECTRE1" );
    if( $erg )
    {   // alten Wert abhaengen und durch neuen ersetzen
      $arr = explode( "SELECTRE1", $dahin );
      $dahin = $arr[0] . "SELECTRE1=$SELECTRE1";
    }
    else	// kein alter Wert, also direkt anhaengen
      $dahin .= "&SELECTRE1=$SELECTRE1";
  }
  if( isset($SELECTRE2) )
  {
    $erg = strstr( $dahin, "SELECTRE2" );
    if( $erg )
    {   // alten Wert abhaengen und durch neuen ersetzen
      $arr = explode( "SELECTRE2", $dahin );
      $dahin = $arr[0] . "SELECTRE2=$SELECTRE2";
    }
    else	// kein alter Wert, also direkt anhaengen
      $dahin .= "&SELECTRE2=$SELECTRE2";
  }
  if( isset($SELECTRE3) )
  {
    $erg = strstr( $dahin, "SELECTRE3" );
    if( $erg )
    {   // alten Wert abhaengen und durch neuen ersetzen
      $arr = explode( "SELECTRE3", $dahin );
      $dahin = $arr[0] . "SELECTRE3=$SELECTRE3";
    }
    else	// kein alter Wert, also direkt anhaengen
      $dahin .= "&SELECTRE3=$SELECTRE3";
  }
  if( isset($SELECTMM1) )
  {
    $erg = strstr( $dahin, "SELECTMM1" );
    if( $erg )
    {   // alten Wert abhaengen und durch neuen ersetzen
      $arr = explode( "SELECTMM1", $dahin );
      $dahin = $arr[0] . "SELECTMM1=$SELECTMM1";
    }
    else	// kein alter Wert, also direkt anhaengen
      $dahin .= "&SELECTMM1=$SELECTMM1";
  }
}
/*** TEST, OB DIESE BENUTZERFUEHRUNG EFFEKTIVER IST:                       ***/
$anker=0;
$a_ = explode( "/", __file__ );
$b_ = $a_[count($a_)-1];
if( isset( $_eCandy ) )
  foreach( $_eCandy as $k => $elem )
    dEcho( $b_, $k . "=" . $elem );
    
if( isset( $_eCandy ) )
  foreach( $_eCandy as $k => $elem )
    if( $elem && isset($candyURL)  && isset($candyURL[$k]) )
    {
      $dahin = $candyURL[$k];
      if( isset($_REQUEST['u']) )
        $dahin .= "&u=" . $_REQUEST['u']; // Tab-Ueberschrift
      $dahin .= "&$k=$elem#$elem";
      $anker="$elem";
    }
if( isset( $dahin ) )
{
  echo"\n<A HREF=\"$dahin\"><em>&lt;&lt; ";
  if( isset($_E['label']) )
    echo $_E['label'];
  else
    echo "fortsetzen";
  echo"</em></A>\n";?>
  <form name='frm' action=""><input type="button" value="schliessen" name="schlie" onclick="self.close()"></form>
  <script language=javascript type='text/javascript'>
  <!--
    document.frm.schlie.focus()
  // -->
  </script>
  <?php
}
if( isset($goto) )
{
  echo "\n<script language=javascript type='text/javascript'>";
  $url = "\n\tlocation.href = '$dahin'";
  echo $url;
  echo "\n</script>\n";
}
?>
