function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
} // await sleep(time);



var command = 0,
    btnslen = 0,
    sentences = [];


document.onkeypress = function(e) {
    e = e || window.event;


    if (e.key == ' ') {
        command = 1; // calculate word count
        console.log("calculating...");
    }

    if (e.key == 'c') {
        command = 2; // make sentence with correct word order 
        console.log("collecting...");
    }



    if (e.key == 'o') {
        command = 3; //print all sentences
    }

};


jomles = ["Laughter is the best medicine", "All 's well that ends well", "He is known all over town", "Every dog has its day",
    "Chin up",
    "The pen is mightier than the sword",
    "Out of sight , out of mind Out",
    "It is raining cats and dogs",
    "That is yesterday 's news",

    "I ’ll keep my fingers crossed for you",
    "German is hard",
    "Too many cooks spoil the broth",
    "The straw that breaks the camel 's back",
    "Practice makes perfect"
]


answer = {}




command = 0


while (1) {

    kalames = []


    var kount = 0;
    for (let j = 0; j < jomles.length; j++) {
        buttons = Array.from(document.getElementsByClassName("notranslate"));
        buttons.forEach(element => {
            element.setAttribute("used", "no");

        });
        btnslen = buttons.length
        jomles[j].split(" ").forEach(element => {



            for (i = 0; i < btnslen; i++) {
                //kalames.push(buttons[i].textContent);
                kalame = buttons[i].textContent;

                if (element == kalame && buttons[i].getAttribute("used") == "no") {
                    answer[kount] = (buttons[i]);
                    buttons[i].setAttribute("used", "yes");
                    kount++;
                    break;
                }
            }




        });
        test = Object.keys(answer).length
        if (btnslen == test) {

            for (let x = 0; x < test; x++) {
                answer[x].click();

            }
            spans = Array.from(document.getElementsByTagName("span"))
            spans.forEach(element => {
                if (element.textContent == "Check")
                    element.click()


            });
            await sleep(250);
            spans = Array.from(document.getElementsByTagName("span"))
            spans.forEach(element => {


                if (element.textContent == "Continue")
                    element.click()

            });


            await sleep(250);

            a = document.getElementsByTagName("svg")
            a = Array.from(a)

            a.forEach(function(ded) {
                if (ded.getAttribute("viewBox") == "0 7155 135 135") {
                    ded.parentNode.click();
                }
            });

            await sleep(150);

            btns = document.getElementsByTagName("button")
            btns = Array.from(btns)
            btns.forEach(function(ded) {
                if (ded.getAttribute("data-test") == "start-button") {
                    ded.click();

                }
            });
            await sleep(250);


            // spans = Array.from(document.getElementsByTagName("span"));



        }
        answer = {};
        kount = 0;


        await sleep(50);
    }




}
