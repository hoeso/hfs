<?php
$debug=1;
if( $debug ) echo"\nDOM-Datei: $_A[xml]<br>";
$ret = $_A['archiveRawDoc']->extract( PCLZIP_OPT_BY_NAME, $_A['xml'], PCLZIP_OPT_EXTRACT_AS_STRING );
if( !$ret )
{
  $modul = $_SERVER['PHP_SELF'];
  echo"domDocAlloc.inc: interner Fehler 02 " . $_A['archiveRawDoc']->errorName() . "<br>";
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}

$versionPHP = explode( ".", phpversion() ); 
if( "5" <= $versionPHP[0] )
{
  $_A['DOMdoc'] = new DOMDocument;
  if( false == $_A['DOMdoc']->loadXML($ret[0]['content']) )
  {
    $modul = $_SERVER['PHP_SELF'];
    echo"domDocAlloc.inc interner Fehler 03<br>";
    $_E['wZu']="anbietendKnopfZurueck";
    include("forkZu.inc");
  }
}
/************ Output *********************************************************
 * new $_A['DOMdoc']: 
 *            	    : 
 *****************************************************************************/
?>
