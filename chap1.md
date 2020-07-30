# Simple Layer for ERP from scratch
## Active Record
Michael Fowler published his Design Pattern ‚Active Record‘ in 2002. In May 2003, no knowledge about Michaels design pattern, I created a similar approach:
```
+----------------+-----------------------------+
| Primary key    | ID                          |
+----------------+-----------------------------+
| Foreign key 1  | <entity1>ID                 |
+----------------+-----------------------------+
| …              | <entityX>ID                 |
+----------------+-----------------------------+
| Foreign key n  | <entityn>ID                 |
+----------------+-----------------------------+
| 1. attribute   | Any name not ending with ID |
+----------------+-----------------------------+
| …              | ./.                         |
| last attribute |                             |
+----------------+-----------------------------+
```

The difference between my and Michaels' design is, that with Michael you can put the foreign keys anywhere in the table, whereas in my convention all foreign keys have to follow the primary key, and after the last foreign key there will be only attributes following.

## Using the Active Record design pattern

The Active Record design pattern is a convention for the database design. The hoeso architecture uses this convention in the application layer.
hoesos underlying theory of its application layer are the three common relations in a relational database:
1. pure entity
2. 1:n entity relationship
3. n:n entity relationship, with the help of a junction entity

A short and simple introduction to this common entity relationship you can find at o‘Reilly, King, Reese, Yarger: MySQL and mSQL

## The idea behind

hoeso now does the following:
It describes the entity or the collaboration of entities which the key points to.

Example:

We have a simple 1:n relation between the entity customer and the entity contactPerson.

'customer' is a pure entity
'contactPerson' is an entity which belongs to 'customer' in the way, that contactPerson needs a foreign key (FK) which points to the customer the contactPerson belongs to.
What hoeso does at this point is to describe the FK of contactPerson as a value which points to a pure entity.

The customer-Entity looks like
```
+-------------+--------+---------------+
| Field       | Type   | Flag          |
+-------------+--------+---------------+
| ID          | int    | autoincrement |
+-------------+--------+---------------+
| CompanyName | String |               |
+-------------+--------+---------------+
| Adress      | String |               |
+-------------+--------+---------------+
```
This entity doesn't have a FK at all so it is a pure entity.

The contactPerson-Entity looks like
```
+------------+--------+---------------+
| Field      | Type   | Flag          |
+------------+--------+---------------+
| ID         | int    | autoincrement |
+------------+--------+---------------+
| customerID | int    |               |
+------------+--------+---------------+
| Name       | string |               |
+------------+--------+---------------+
| telephone  | string |               |
+------------+--------+---------------+
| email      | string |               |
+------------+--------+---------------+
```

contactPerson has one FK. There can be one or more instances in contactPerson which point to an instance in customer which means that is a 1:n relationship.
hoeso describes that in an application layer, e.g. using name-value pairs in a html-application:
```
+------+-------------------------------------------------------------------+------------------+
| Name | Meaning                                                           | Example          |
+------+-------------------------------------------------------------------+------------------+
| a    | destination entity which will receive the sql-insert data         | ?a=contactPerson |
+------+-------------------------------------------------------------------+------------------+
| pe   | how many fk of type pure entity does the destination entity have? | &pe=1            |
+------+-------------------------------------------------------------------+------------------+
| pe1  | Name of the pure entity where the first FK of that type points to | &pe1=customer    |
+------+-------------------------------------------------------------------+------------------+
```

So the link to a html-form which receives data of a contactPerson could be e.g.


`<a "href=some.php?a=contactPerson&pe=1&pe1=customer">Contact Person</a>`

That's all! Of course you need some a bit of php-code which provides the task, but once it is implemented you do nothing more than describe the FKs of the destination entity in the future.
From now on let's call this approach **active key** design pattern.

