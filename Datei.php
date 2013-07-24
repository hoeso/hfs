<?php
class Datei
{
  protected $fp;
  private $pfad;
  private $mode;
  function __construct($d, $mode="r")
  {
    $this->pfad = $d;
    $this->mode = $mode;
    $this->open();
  }
  function __get($var)
  {
    switch($var)
    {
      case 'handle':
        return $this->fp;
      case 'lesbar':
        return $this->fp <> 0;
      default:
        throw new Exception("Datei hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
  function reset()
  {
    fclose( $this->fp );
  }
  function open()
  {
    $this->fp = fopen( $this->pfad, $this->mode );
    if( !$this->fp )
    {
      throw new Exception("Fehler beim &Ouml;ffnen von $this->pfad.", 1 );
      return false;
    }
    return true;
  }
}
