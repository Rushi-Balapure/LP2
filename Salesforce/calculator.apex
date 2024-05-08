public class Calculator {
    public Integer add(Integer a, Integer b) {
        return a + b;
    }

    public Integer subtract(Integer a, Integer b) {
        return a - b;
    }

    public Integer multiply(Integer a, Integer b) {
        return a * b;
    }

    public Integer divide(Integer a, Integer b) {
        if (b == 0) {
            System.debug('Error');
            return 0;
        }
        return a / b;
    }

    public Long power(Integer a, Integer b) {
        if (b < 0) {
            System.debug('Wrong input');
            return 0;
        }
        Long result = 1;
        for (Integer i = 0; i < b; i++) {
            result *= a;
        }
        return result;
    }

    public Double logg(Double a) {
        if (a <= 0) {
            System.debug('Error');
            return 0;
        }
        return Math.log(a);
    }
}