<?
$arrFK = array(
/*zum Kopieren:
	""=>array( // ich bin die Entitaet
		"",// ich bin ein Fremdschluessel
	),
*/
	"Auftrag"=>array(
		"Regulierer",
	),
	"Auftragabrechnung"=>array(
		"Tarif",
	),
	"Bearbeiter"=>array(
		"PortalUser",
		"Schadenbuero",
	),
	"Beistellung"=>array( // ich bin die Entitaet
		"Angebot",// ich bin ein Fremdschluessel
	),
	"BerichtSparteTarif"=>array(
		"Bericht",
		"Sparte",
		"Tarif",
	),
	"CenterController"=>array(
		"Regulierer",
	),
	"Controllinggebuehr"=>array( // ich bin die Entitaet
		"Zeitstempel",// ich bin ein Fremdschluessel
	),
	"ControllinggebuehrEingang"=>array( // ich bin die Entitaet
		"Zeitstempel",// ich bin ein Fremdschluessel
	),
	"Innendienst"=>array(
		"Regulierer",
	),
	"Portal"=>array(
		"Center",
		"Bearbeiter",
		"Tarif",
	),
	"Port"=>array(
		"Regulierer",
	),
	"Rechnungabsender"=>array(
		"Center",
	),
	"RechnungempfaengerVersicherer"=>array(
		"Versicherer",
	),
/*	"ReguliererRegion"=>array( // ich bin die Entitaet
		"Regulierer",// ich bin ein Fremdschluessel
	),*/
	"Schadenbuero"=>array(
		"Versicherer",
	),
/*zum Kopieren:
	""=>array(
		"",
	),
*/
);
?>
