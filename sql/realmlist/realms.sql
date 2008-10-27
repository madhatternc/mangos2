-- MySQL dump 10.11
--
-- Host: localhost    Database: mangos2-realmlist
-- ------------------------------------------------------
-- Server version	5.0.67-0ubuntu6

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `realms`
--

DROP TABLE IF EXISTS `realms`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `realms` (
  `name` varchar(32) collate utf8_unicode_ci NOT NULL,
  `address` varchar(32) collate utf8_unicode_ci NOT NULL,
  `population` float(5,3) unsigned NOT NULL default '0.000',
  `color` tinyint(3) unsigned NOT NULL default '0',
  `type` tinyint(3) unsigned NOT NULL default '0',
  `locked` tinyint(4) NOT NULL,
  `online` tinyint(1) NOT NULL default '0',
  `language` tinyint(3) NOT NULL default '0',
  `players` tinyint(5) NOT NULL default '0',
  `gms` tinyint(5) NOT NULL default '0',
  PRIMARY KEY  (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Storage for world servers, and their status.';
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `realms`
--

LOCK TABLES `realms` WRITE;
/*!40000 ALTER TABLE `realms` DISABLE KEYS */;
INSERT INTO `realms` VALUES
('Aerie Peak','127.0.0.1:8129',0.500,0,0,0,1,1,0,0),
('Agamaggan','127.0.0.2:8129',0.555,0,1,0,1,1,0,0),
('Alexstrasza','127.0.0.5:8129',1.555,0,0,0,1,2,0,0),
('Anetheron','127.0.0.6:8129',1.555,0,1,0,1,2,0,0),
('Dalaran','127.0.0.9:8129',1.555,0,0,0,1,3,0,0),
('Darkmoon Faire','127.0.0.3:8129',0.500,0,6,0,1,1,0,0),
('Das Syndikat','127.0.0.8:8129',0.955,0,8,0,1,2,0,0),
('Garona','127.0.0.10:8129',1.555,0,1,0,1,3,0,0),
('Los Errantes','127.0.0.15:8129',0.955,0,6,0,1,5,0,0),
('Minahonda','127.0.0.13:8129',1.555,0,0,0,1,5,0,0),
('Shen\'dralar','127.0.0.16:8129',0.955,0,8,0,1,5,0,0),
('Uldum','127.0.0.14:8129',1.555,0,1,0,1,5,0,0);
/*!40000 ALTER TABLE `realms` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2008-10-23 22:12:43
