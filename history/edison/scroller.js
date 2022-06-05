function goToID(id) {
    console.log(`going to element ${id}`);
    document.getElementById(id).scrollIntoView({ behavior: "smooth" });
}

function changeClass(object, oldClass, newClass) {
    console.log(`changing class ${oldClass} of object ${object} to ${newClass}`)
    var regExp = new RegExp('(?:^|\\s)' + oldClass + '(?!\\S)', 'g');
    object.className = object.className.replace(regExp, newClass);
}

setTimeout(() => {
    (function myLoop(i) {
        setTimeout(function() {
            if (i != 1) {
                console.log(`event_${10-i}`);
                goToID(id = `event_${10-i}`);
            }
            if ((9 - i < 8) & (9 - i > -1)) {
                console.log(`slide_${9-i}`)
                goToID(`slide_${9-i}`)
            }
            if (i != 10) {
                changeClass(object = document.getElementById(`event_${9-i}`), oldClass = "timeline-event-enabled", newClass = "timeline-event");
            }
            if (i > 1) {
                changeClass(object = document.getElementById(`event_${10-i}`), oldClass = "timeline-event", newClass = "timeline-event-enabled");
            }
            if (--i) myLoop(i); //  decrement i and call myLoop again if i > 0
        }, 4500)
    })(10); //  pass the number of iterations as an argument
}, 5000);