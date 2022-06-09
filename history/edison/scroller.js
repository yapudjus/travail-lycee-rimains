function goToID(id) {
    console.log(`going to element ${id}`);
    document.getElementById(id).scrollIntoView({ behavior: "smooth" });
}

function changeClass(object, oldClass, newClass) {
    console.log(`changing class ${oldClass} of object ${object} to ${newClass}`)
    var regExp = new RegExp('(?:^|\\s)' + oldClass + '(?!\\S)', 'g');
    object.className = object.className.replace(regExp, newClass);
}

var slidecount = 9;

setTimeout(() => {
    (function myLoop(i) {
        setTimeout(function() {
            if (i != 1) {
                console.log(`event_${slidecount+3-i}`);
                goToID(id = `event_${slidecount+3-i}`);
            }
            if ((slidecount + 2 - i < slidecount + 1) & (slidecount + 2 - i > -1)) {
                console.log(`slide_${slidecount+2-i}`)
                goToID(`slide_${slidecount+2-i}`)
            }
            if (i != slidecount + 3) {
                changeClass(object = document.getElementById(`event_${slidecount+2-i}`), oldClass = "timeline-event-enabled", newClass = "timeline-event");
            }
            if (i > 1) {
                changeClass(object = document.getElementById(`event_${slidecount+3-i}`), oldClass = "timeline-event", newClass = "timeline-event-enabled");
            }
            if (--i) myLoop(i); //  decrement i and call myLoop again if i > 0
        }, 20000)
    })(slidecount + 3); //  pass the number of iterations as an argument
}, 5000);
