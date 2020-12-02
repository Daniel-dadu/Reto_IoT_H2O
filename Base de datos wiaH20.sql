-- --------------------------------------------------------

-- BASE DE DATOS: RETO IoT

-- --------------------------------------------------------

CREATE DATABASE IF NOT EXISTS wiah20 DEFAULT CHARACTER SET utf8 COLLATE utf8_spanish_ci;
USE wiah20;

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

-- --------------------------------------------------------

-- TABLA PARA LA VARIABLE

CREATE TABLE IF NOT EXISTS variable(
  idVariable int(11) NOT NULL,
  nombre varchar(50) COLLATE utf8_spanish_ci NOT NULL,
  valor float NOT NULL,
  fecha varchar(50) COLLATE utf8_spanish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;

ALTER TABLE variable
  ADD PRIMARY KEY (idVariable),
  ADD UNIQUE KEY idVariable (idVariable);

ALTER TABLE variable
  MODIFY idVariable int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
COMMIT;

-- FIN

-- ---------------------------------------------------------