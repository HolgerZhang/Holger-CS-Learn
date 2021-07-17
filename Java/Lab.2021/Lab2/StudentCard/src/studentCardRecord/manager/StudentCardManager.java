package studentCardRecord.manager;

import studentCardRecord.entity.Card;
import studentCardRecord.entity.Record;
import studentCardRecord.entity.Student;

import java.util.*;

public class StudentCardManager {
    private final List<Student> students;
    private final Map<String, Card> cards;
    private final Map<String, String> studentCardMap;

    public StudentCardManager() {
        this.students = new ArrayList<>();
        this.cards = new HashMap<>();
        this.studentCardMap = new HashMap<>();
    }

    public void addStudent(String id, String name, int year, String major, String phone) {
        this.students.add(new Student(id, name, year, major, phone));
    }

    public void linkStudentCard(String studentId, String cardId) {
        this.cards.put(cardId, new Card(cardId));
        this.studentCardMap.put(studentId, cardId);
    }

    public Card findCardByCardId(String id) {
        return this.cards.getOrDefault(id, null);
    }

    public Card findCardByStudentId(String id) {
        if (!this.studentCardMap.containsKey(id)) {
            return null;
        }
        return this.findCardByCardId(this.studentCardMap.get(id));
    }

    public void addRecord(String cardId, Record.RecordType type, double amount, int place) {
        Card card = this.findCardByCardId(cardId);
        if (card == null) {
            throw new NoSuchElementException("未能找到卡号为" + cardId + "的一卡通");
        }
        card.insert(new Record(cardId, type, amount, place));
    }

    public List<Student> getStudents() {
        return students;
    }

}
