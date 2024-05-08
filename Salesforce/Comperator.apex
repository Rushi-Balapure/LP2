public class Comperator {
    public void compare(Integer a, Integer b, Integer c) {
        if (a > b && a > c) {
            System.debug('a is the largest number.');
        } else if (b > a && b > c) {
            System.debug('b is the largest number.');
        } else {
            System.debug('c is the largest number.');
        }
    }
}