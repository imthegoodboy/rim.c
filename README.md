 
# Program 1

```sql
-- Program 1
-- Employee Table with Constraints and Rollback

CREATE USER 'raj2'@'localhost' IDENTIFIED BY 'raj2';

GRANT ALL PRIVILEGES ON raj.* TO 'raj2'@'localhost';

FLUSH PRIVILEGES;

CREATE DATABASE raj;

USE raj;

CREATE TABLE Employee (
    EMPNO INT,
    ENAME VARCHAR(20),
    JOB VARCHAR(20),
    MANAGER_NO INT,
    SAL DECIMAL(10,2),
    COMMISSION DECIMAL(10,2)
);

DESC Employee;

INSERT INTO Employee
VALUES (101, 'Ravi', 'Manager', 201, 50000, 5000);

INSERT INTO Employee
VALUES (102, 'Anita', 'Clerk', 101, 20000, 1000);

INSERT INTO Employee
VALUES (103, 'Suresh', 'Salesman', 101, 25000, 2000);

SELECT * FROM Employee;

SET AUTOCOMMIT = 0;

INSERT INTO Employee
VALUES (104, 'Mahesh', 'Watchman', 104, 243400, 2400);

SELECT * FROM Employee;

ROLLBACK;

SELECT * FROM Employee;

ALTER TABLE Employee
ADD CONSTRAINT emp_pk PRIMARY KEY (EMPNO);

ALTER TABLE Employee
MODIFY ENAME VARCHAR(10) NOT NULL;

DESC Employee;

INSERT INTO Employee
VALUES (104, NULL, 'Watchman', 104, 243400, 2400);
```

---

# Program 2

```sql
-- Program 2
-- Employee Table Operations

CREATE TABLE Employee (
    EMPNO INT PRIMARY KEY,
    ENAME VARCHAR(50) NOT NULL,
    JOB VARCHAR(30),
    MGR INT,
    SAL DECIMAL(10,2)
);

ALTER TABLE Employee
ADD COMMISSION DECIMAL(10,2)
CHECK (COMMISSION >= 0);

INSERT INTO Employee
(EMPNO, ENAME, JOB, MGR, SAL, COMMISSION)
VALUES
(101, 'Ramesh', 'Manager', NULL, 75000, 5000),
(102, 'Suresh', 'Clerk', 101, 25000, 1000),
(103, 'Mahesh', 'Analyst', 101, 45000, 3000),
(104, 'Anita', 'HR', 101, 40000, 2000),
(105, 'Kiran', 'Salesman', 101, 30000, 1500);

SELECT * FROM Employee;

UPDATE Employee
SET JOB = 'Senior Clerk'
WHERE EMPNO = 102;

SELECT EMPNO, ENAME, JOB
FROM Employee
WHERE EMPNO = 102;

ALTER TABLE Employee
CHANGE JOB DESIGNATION VARCHAR(30);

DESC Employee;

DELETE FROM Employee
WHERE EMPNO = 105;

SELECT * FROM Employee;
```

---

# Program 3

```sql
-- Program 3
-- Aggregate Functions, GROUP BY and ORDER BY

CREATE DATABASE program03;

USE program03;

CREATE TABLE Employee (
    E_id INT PRIMARY KEY,
    E_name VARCHAR(50),
    Age INT,
    Salary DECIMAL(10,2)
);

INSERT INTO Employee VALUES
(101, 'Ravi', 25, 30000),
(102, 'Anita', 30, 45000),
(103, 'Kiran', 28, 35000),
(104, 'Suresh', 35, 50000),
(105, 'Meena', 27, 40000);

SELECT * FROM Employee;

SELECT COUNT(E_name) AS Total_Employees
FROM Employee;

SELECT MAX(Age) AS Maximum_Age
FROM Employee;

SELECT MIN(Age) AS Minimum_Age
FROM Employee;

SELECT E_name, Salary
FROM Employee
ORDER BY Salary ASC;

SELECT Salary,
COUNT(*) AS Number_of_Employees
FROM Employee
GROUP BY Salary;

INSERT INTO Employee
VALUES (106, 'Vikram', 26, 30000);

SELECT Salary,
COUNT(*) AS Number_of_Employees
FROM Employee
GROUP BY Salary;
```

---

# Program 4

```sql
-- Program 4
-- Row Level Trigger on CUSTOMERS Table

CREATE TABLE CUSTOMERS (
    ID INT PRIMARY KEY,
    NAME VARCHAR(50),
    AGE INT,
    ADDRESS VARCHAR(100),
    SALARY DECIMAL(10,2)
);

INSERT INTO CUSTOMERS
VALUES (10, 'Abhi', 25, 'Bangalore', 10000);

INSERT INTO CUSTOMERS
VALUES (20, 'Mukund', 35, 'Mangalore', 20000);

INSERT INTO CUSTOMERS
VALUES (30, 'Shiva', 34, 'Jaipur', 30000);

SELECT * FROM CUSTOMERS;

CREATE TABLE customer_salary_log (
    id INT AUTO_INCREMENT PRIMARY KEY,
    customer_id INT,
    action_type VARCHAR(10),
    old_salary DECIMAL(10,2),
    new_salary DECIMAL(10,2),
    difference DECIMAL(10,2),
    log_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

DELIMITER //

CREATE TRIGGER trg_customers_insert
AFTER INSERT ON CUSTOMERS
FOR EACH ROW
BEGIN
    INSERT INTO customer_salary_log
    (customer_id, action_type, old_salary, new_salary, difference)
    VALUES
    (NEW.ID, 'INSERT', NULL, NEW.SALARY, NEW.SALARY);
END //

DELIMITER ;

DELIMITER //

CREATE TRIGGER trg_customers_update
AFTER UPDATE ON CUSTOMERS
FOR EACH ROW
BEGIN
    INSERT INTO customer_salary_log
    (customer_id, action_type, old_salary, new_salary, difference)
    VALUES
    (NEW.ID, 'UPDATE', OLD.SALARY, NEW.SALARY,
     NEW.SALARY - OLD.SALARY);
END //

DELIMITER ;

DELIMITER //

CREATE TRIGGER trg_customers_delete
AFTER DELETE ON CUSTOMERS
FOR EACH ROW
BEGIN
    INSERT INTO customer_salary_log
    (customer_id, action_type, old_salary, new_salary, difference)
    VALUES
    (OLD.ID, 'DELETE', OLD.SALARY, NULL,
     -OLD.SALARY);
END //

DELIMITER ;

INSERT INTO CUSTOMERS
VALUES (40, 'Dhruv', 45, 'Bombay', 50000);

SELECT * FROM customer_salary_log;

UPDATE CUSTOMERS
SET SALARY = 35000
WHERE ID = 10;

SELECT * FROM CUSTOMERS;

SELECT * FROM customer_salary_log;

DELETE FROM CUSTOMERS
WHERE ID = 40;

SELECT * FROM CUSTOMERS;

SELECT * FROM customer_salary_log;
```

---

# Program 5

```sql
-- Program 5
-- Cursor Example for Employee Salary Increment

CREATE TABLE employee (
    eid INT,
    ename VARCHAR(15),
    age INT,
    sal INT
);

INSERT INTO employee VALUES
(10, 'abhi', 35, 10000),
(20, 'rohith', 30, 9000),
(30, 'david', 28, 9000),
(40, 'rahul', 25, 4000),
(50, 'pramod', 23, 5000),
(60, 'suraj', 19, 3500);

SELECT * FROM employee;

SHOW PROCEDURE STATUS
WHERE db = 'your_database_name';

DROP PROCEDURE IF EXISTS cursor_demo_sal_increment;

DELIMITER $$

CREATE PROCEDURE cursor_demo_sal_increment()

BEGIN

    DECLARE v_eid INT;
    DECLARE v_sal INT;

    DECLARE completed INT DEFAULT 0;

    DECLARE c1 CURSOR FOR
    SELECT eid, sal FROM employee;

    DECLARE CONTINUE HANDLER
    FOR NOT FOUND
    SET completed = 1;

    OPEN c1;

    read_loop: LOOP

        FETCH c1 INTO v_eid, v_sal;

        IF completed THEN
            LEAVE read_loop;
        END IF;

        IF v_sal > 5000 THEN

            UPDATE employee
            SET sal = v_sal * 1.10
            WHERE eid = v_eid;

            SELECT CONCAT(v_eid, ' ', v_sal,
            ' increased by 10%')
            AS 'emp id emp sal';

        ELSE

            UPDATE employee
            SET sal = v_sal * 1.20
            WHERE eid = v_eid;

            SELECT CONCAT(v_eid, ' ', v_sal,
            ' increased by 20%')
            AS 'emp id emp sal';

        END IF;

    END LOOP;

    CLOSE c1;

END$$

DELIMITER ;

CALL cursor_demo_sal_increment();

SELECT * FROM employee;
```
