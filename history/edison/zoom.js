setTimeout(() => {
    // Get the modal
    var modal = document.getElementById('myModal');
    // Get the image and insert it inside the modal - use its "alt" text as a caption
    var modalImg = document.getElementById("img01");
    var captionText = document.getElementById("caption");
    const img_zooms = [
        "dsgf",
        "rg12",
        "edg5",
        "ers6",
        "apc4"
    ]
    for (let i = 0; i < img_zooms.length; i++) {
        console.log(`img_zooms[${i}] = ${img_zooms[i]}`);
        console.log(`document.getElementById(${img_zooms[i]}) = ${document.getElementById(img_zooms[i])}`);
        var img = document.getElementById(`${img_zooms[i]}_img`);
        img.onclick = function() {
            modal.style.display = "block";
            modalImg.src = this.src;
            modalImg.alt = this.alt;
            captionText.innerHTML = this.alt;
        }
    }

    // When the user clicks on <span> (x), close the modal
    modal.onclick = function() {
        img01.className += " out";
        setTimeout(function() {
            modal.style.display = "none";
            img01.className = "modal-content";
        }, 400);

    }
}, 5000);