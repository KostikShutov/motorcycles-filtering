CREATE TABLE "class_descriptions" (
  "id" integer NOT NULL PRIMARY KEY AUTOINCREMENT,
  "class_id" integer NOT NULL,
  "sign_id" integer NOT NULL,
  FOREIGN KEY ("class_id") REFERENCES "classes" ("id") ON DELETE CASCADE ON UPDATE NO ACTION,
  FOREIGN KEY ("sign_id") REFERENCES "signs" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);


CREATE TABLE "classes" (
  "id" integer NOT NULL PRIMARY KEY AUTOINCREMENT,
  "name" text(25) NOT NULL
);

CREATE UNIQUE INDEX "classes_name" ON "classes" ("name");


CREATE TABLE "signs" (
  "id" integer NOT NULL PRIMARY KEY AUTOINCREMENT,
  "name" text(25) NOT NULL,
  "type" integer NULL DEFAULT '0'
);

CREATE UNIQUE INDEX "signs_name" ON "signs" ("name");


CREATE TABLE "signs_dimensional" (
  "id" integer NOT NULL PRIMARY KEY AUTOINCREMENT,
  "sign_id" integer NOT NULL,
  "interval_start" integer NOT NULL,
  "interval_end" integer NOT NULL,
  "unit" text(25) NOT NULL,
  FOREIGN KEY ("sign_id") REFERENCES "signs" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);


CREATE TABLE "signs_logical" (
  "id" integer NOT NULL PRIMARY KEY AUTOINCREMENT,
  "sign_id" integer NOT NULL,
  "name_yes" text(25) NOT NULL,
  "name_no" text(25) NOT NULL,
  FOREIGN KEY ("sign_id") REFERENCES "signs" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);


CREATE TABLE "signs_scalar" (
  "id" integer NOT NULL PRIMARY KEY AUTOINCREMENT,
  "sign_id" integer NOT NULL,
  "name" text(25) NOT NULL,
  FOREIGN KEY ("sign_id") REFERENCES "signs" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);


CREATE TABLE sqlite_sequence(name,seq);


CREATE TABLE "values_dimensional" (
  "id" integer NOT NULL PRIMARY KEY AUTOINCREMENT,
  "class_descriptions_id" integer NOT NULL,
  "interval_start" integer NOT NULL,
  "interval_end" integer NOT NULL,
  "signs_id" integer NOT NULL,
  "active" integer NOT NULL DEFAULT '0',
  FOREIGN KEY ("class_descriptions_id") REFERENCES "class_descriptions" ("id") ON DELETE CASCADE ON UPDATE NO ACTION,
  FOREIGN KEY ("signs_id") REFERENCES "signs_dimensional" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);

CREATE UNIQUE INDEX "values_dimensional_class_descriptions_id" ON "values_dimensional" ("class_descriptions_id");


CREATE TABLE "values_logical" (
  "id" integer NOT NULL PRIMARY KEY AUTOINCREMENT,
  "class_descriptions_id" integer NOT NULL,
  "yes" integer NOT NULL DEFAULT '0',
  "no" integer NOT NULL DEFAULT '0',
  "signs_id" integer NOT NULL,
  FOREIGN KEY ("signs_id") REFERENCES "signs_logical" ("id") ON DELETE CASCADE ON UPDATE NO ACTION,
  FOREIGN KEY ("class_descriptions_id") REFERENCES "class_descriptions" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);

CREATE UNIQUE INDEX "values_logical_class_descriptions_id" ON "values_logical" ("class_descriptions_id");


CREATE TABLE "values_scalar" (
  "id" integer NOT NULL PRIMARY KEY AUTOINCREMENT,
  "class_descriptions_id" integer NOT NULL,
  "sign_id" integer NOT NULL,
  "active" integer NOT NULL DEFAULT '0',
  FOREIGN KEY ("class_descriptions_id") REFERENCES "class_descriptions" ("id") ON DELETE CASCADE ON UPDATE NO ACTION,
  FOREIGN KEY ("sign_id") REFERENCES "signs_scalar" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);