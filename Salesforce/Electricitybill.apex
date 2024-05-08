public class ElectricityBillCalculator {
    public static void CalculateBill(Decimal units){
        Decimal rate=1;
        if(units<100){
            rate=4.3;
        }else if(units<200){
            rate=6.4;
        }else if(units<300){
            rate=8.8;
        }else if(units<400){
          rate=10.2;
        }else{
            rate=13.4;
        }
        Decimal ans = units*rate;
        ans = ans*1.05;
        System.debug('For '+units+' units rate is '+rate+' ,total amount to be paid (5% GST.)= '+ans +'/- Rs.');
    }
}