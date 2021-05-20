use mysql;

# /////////////// Tabelle 'user' //////////////////////////////////
# ////////////////////////////////////////////////////////////////
INSERT IGNORE  INTO user (Host, User) VALUES ('localhost','hfs');
UPDATE user SET authentication_string = PASSWORD('') WHERE 'hfs'=user AND Host='localhost';

# /////////////// Tabelle 'db' ////////////////////////////////////
# ////////////////////////////////////////////////////////////////
# LOCK TABLES fuer mysqldump:
INSERT IGNORE  INTO db (Host, Db, User, Select_Priv, Insert_Priv, Update_Priv, Delete_Priv, Lock_tables_priv) VALUES ('localhost','sarscov2t','hfs','Y','Y','Y','Y','Y');

FLUSH PRIVILEGES;
