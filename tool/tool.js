console.log(calcFbaud(1,0,4000));
console.log(4000/16);

function calcFbaud(bscale, bsel, fper){
 if (bscale < 0) {
   return fper/(16*((bsel*2^bscale)+1));
 }
 else{
   return fper/((2^bscale)*(16*(bsel+1)));
 }
}
