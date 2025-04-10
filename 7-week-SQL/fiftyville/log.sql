-- Keep a log of any SQL queries you execute as you solve the mystery.
-- First let's start with the table named crime_scene_reports
SELECT distinct month FROM crime_scene_reports;
SELECT description FROM crime_scene_reports WHERE year = 2024 AND day = 28 AND month = 7 AND street = 'Humphrey Street';
-- Examine interviews.
SELECT name, transcript FROM interviews WHERE year = 2024 AND month = 7 AND day = 28;

select activity,license_plate, year, month, day, hour, minute from bakery_security_logs
where year = 2024 and day = 28 and month = 7;
--Активность на стоянке - пока ничего, без точного времени нет решения.
select f.id, orig.city, des.city, f.hour from flights f
join airports orig ON f.origin_airport_id = orig.id
join airports des on f.destination_airport_id = des.id
where f.year = 2024 and f.month = 7 and f.day = 29 order by f.hour;

--Сообщник купил билет в 8 утра в Нью Йорк. Узнали id сделаем другой запрос, чтобы узнать, кто купил билет и пассажира.

select * from people join passengers on people.passport_number = passengers.passport_number where passengers.flight_id = 36;
--Имена, номера всез на рейсе. Теперь нужно посмотреть на стоянке номерные знаки и знаки свзяанные с этими людьми.

select * from bakery_security_logs
where year = 2024 and month = 7 and day = 28 and
license_plate in (select license_plate from people join passengers on people.passport_number = passengers.passport_number where passengers.flight_id = 36);
--Все номера связанные с пассажирами на самолете. Теперь Нужно проверить звонки. После того как покинул пекарню, был звонок длительностью меньше минуты.
select * from atm_transactions where year = 2024 and month = 7 and day = 28 and atm_location = 'Leggett Street';
--Кто снимал бабки с утра. Но тут время не указано. По номеру аккаунта в банк можно осмотреть

select license_plate from people where id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where year = 2024 and month = 7 an
d day = 28 and atm_locati^C = 'Leggett Street'))

-- Получаем номера машин людей, которые снимали деньги 28 июля. Сравним с номерами, которые мы получим
SELECT people.name, people.license_plate, people.phone_number
FROM people
WHERE people.license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2024
      AND month = 7
      AND day = 28
      AND license_plate IN (
          SELECT license_plate
          FROM people
          JOIN passengers ON people.passport_number = passengers.passport_number
          WHERE passengers.flight_id = 36
      )
    INTERSECT
    SELECT license_plate
    FROM people
    WHERE id IN (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number
            FROM atm_transactions
            WHERE year = 2024
              AND month = 7
              AND day = 28
              AND atm_location = 'Leggett Street'
        )
    )
);


SELECT *
FROM people
WHERE people.license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2024
      AND month = 7
      AND day = 28
      AND hour >= 10
      AND minute < 25
      AND license_plate IN (
          SELECT license_plate
          FROM people
          JOIN passengers ON people.passport_number = passengers.passport_number
          WHERE passengers.flight_id = 36
      )
    INTERSECT
    SELECT license_plate
    FROM people
    WHERE id IN (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number
            FROM atm_transactions
            WHERE year = 2024
              AND month = 7
              AND day = 28
              AND atm_location = 'Leggett Street'
              AND transaction_type = 'withdraw'
        )
    )
)
AND people.phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2024
      AND month = 7
      AND day = 28
      AND duration < 60
);
-- Теперь сравним время и получается в 10 часов в 18 минут выехал у нас Брюс. Въехал в пекарню в 8 часов 23 минуты. Брюс главный подозреваемый. Осталось найти сообщника
SELECT *
FROM phone_calls
WHERE caller IN (
    SELECT phone_number
    FROM people
    WHERE id = 686048
)
AND duration < 60
AND year = 2024
AND month = 7
AND day = 28;
-- Нашли мы номер соучастника. Осталось пробить по таблице "Людишки"
SELECT *
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE caller IN (
        SELECT phone_number
        FROM people
        WHERE id = 686048
    )
    AND duration < 60
    AND year = 2024
    AND month = 7
    AND day = 28
);
-- Вот и нашли Робина. Вроде все.
-- Простите, что на русском. Задача сложнее, чем мне показалась на первый взгляд. На английском уже не смог дальше думать.
-- А записи тут использовал только для себя. Как черновик. Хотел красивые запросы написать,в  итоге очень увлекся именно
-- идеей найти вора и уже забил на все, просто делал задачу. А переписывать уже решение и переводить сил нет =)
-- Это была одна из самых интересных задач, которые я видел в своей жизни. Спасибо вам за неё.
