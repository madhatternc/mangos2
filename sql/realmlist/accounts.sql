-- MySQL dump 10.11
--
-- Host: localhost    Database: mangos2-realm
-- ------------------------------------------------------
-- Server version   5.0.45-Debian_1ubuntu3-log

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
-- Table structure for table `accounts`
--

DROP TABLE IF EXISTS `accounts`;
CREATE TABLE `accounts` (
  `login` varchar(32) NOT NULL default '',
  `password` varchar(32) NOT NULL default '',
  `level` tinyint(1) NOT NULL default '0',
  `authip` varchar(20) NOT NULL default '0.0.0.0',
  `sessionkey` varchar(80) NOT NULL default '',
  `email` varchar(100) NOT NULL default '',
  `joindate` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `lastlogin` timestamp NOT NULL default '0000-00-00 00:00:00',
  `banned` tinyint(1) unsigned NOT NULL default '0',
  `data0` mediumtext NOT NULL,
  `data1` mediumtext NOT NULL,
  `data2` mediumtext NOT NULL,
  PRIMARY KEY  (`login`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Storage for basic authentication data, and account settings.';

--
-- Dumping data for table `accounts`
--

LOCK TABLES `accounts` WRITE;
/*!40000 ALTER TABLE `accounts` DISABLE KEYS */;
INSERT INTO `accounts` VALUES
('DEVEL','test',4,'','','test@getmangos.com','2007-11-28 18:34:41','2005-05-13 22:00:00',0,'','',''),
('GM','test',3,'','','test@getmangos.com','2007-11-28 18:34:41','2005-05-13 22:00:00',0,'','',''),
('SEER','test',2,'','','test@getmangos.com','2007-11-28 18:34:41','2005-05-13 22:00:00',0,'','',''),
('COUNCELOR','test',1,'','','test@getmangos.com','2007-11-28 18:34:41','2005-05-13 22:00:00',0,'','',''),
('PLAYER','test',0,'','','test@getmangos.com','2007-11-28 18:34:41','2005-05-13 22:00:00',0,'','',''),
('TEST','test',0,'','','test@getmangos.com','2007-11-28 18:34:41','2005-05-13 22:00:00',0,'','','');
/*!40000 ALTER TABLE `accounts` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2007-11-28 18:50:55
