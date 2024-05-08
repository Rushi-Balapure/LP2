public class CurrencyConverter {
  public static void convert(Integer inr,String curren){
        Decimal div=1;
        if(curren=='US Dollar'){
            div = 83.8;
        }else if(curren=='Euro'){
            div = 90;
        }else if(curren=='British Pound'){
            div = 104.9;
        }else if(curren=='Japanese Yen'){
            div = 0.54;
        }else if(curren=='Rial'){
            div = 0.02;
        }else if(curren=='Dinar'){
            div = 271.5;
        }else{
            System.debug('Enter valid input');
            return;
        }
        Decimal rate = inr/div;
        System.debug(inr+' Rupees is equal to '+rate+' '+curren);
    }
}