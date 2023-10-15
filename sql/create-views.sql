DROP VIEW IF EXISTS CARD_VIEW;

DROP VIEW IF EXISTS STUDY_FILE_STATUS;

CREATE VIEW CARD_VIEW AS
SELECT C.ID, Q.QUESTION, A.ANSWER FROM CARD C
INNER JOIN QUESTION Q ON Q.ID = C.QUESTION_ID
INNER JOIN ANSWER A ON A.ID = C.ANSWER_ID;

CREATE VIEW STUDY_FILE_STATUS as
select count(sf.topic_card_id) as NUM_CARDS, t.id as TOPIC_ID, t.topic,sf.box_id from study_file sf
inner join topic_card tc on tc.id = sf.topic_card_id
inner join topic t on t.id = tc.topic_id
group by t.id, sf.box_id
order by sf.box_id, t.id;
