public class CelciusToFerenhite {
    public static void converter(Decimal cel){
        Decimal feren = 32 + (9*cel)/5;
        System.debug(cel+' degree celcius = '+feren+' ferenhite');
    }
}
    