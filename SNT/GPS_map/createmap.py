
import folium
c= folium.Map(location=[48.647647158, -2.00400],zoom_start=20)
rim = folium.Html("""<style>
        ul { list-style-type: none; margin: 15px; padding: 10px; width: fit-content; }
        li a { display: block; font-family: arial; font-size: 1.2em; font-weight: bold; padding: 10px; text-decoration: none; }
        li a:hover { background-color: #ddd; }
        li .title { left: 50%; margin: 0; padding: 0; position: relative; }
    </style>
    <ul>
        <li class="title">
            <b>Lycée les rimains</b>
        </li>
        <li>
            <iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d1016.3266479248483!2d-2.0028717983855153!3d48.64763842343327!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x480e8163a31187c9%3A0x3beb9ba76aafe124!2sLyc%C3%A9e%20g%C3%A9n%C3%A9ral%20et%20technologique%20Les%20Rimains!5e0!3m2!1sfr!2sfr!4v1654248214795!5m2!1sfr!2sfr" width="600" height="450" style="border:0;" allowfullscreen="" loading="lazy" referrerpolicy="no-referrer-when-downgrade"></iframe>
        </li>
    </ul>"""
, script=True)
folium.Marker([48.647647158,  -2.00400],popup=folium.Popup(rim, max_width=2650)).add_to(c)
# folium.Marker([45.514688,-73.566438], popup="CEGEP du vieux montréal").add_to(c)
cegep = folium.Html("""<style>
        ul { list-style-type: none; margin: 15px; padding: 10px; width: fit-content; }
        li a { display: block; font-family: arial; font-size: 1.2em; font-weight: bold; padding: 10px; text-decoration: none; }
        li a:hover { background-color: #ddd; }
        li .title { left: 50%; margin: 0; padding: 0; position: relative; }
    </style>
    <ul>
        <li class="title">
            <b>CEGEP du vieux montréal</b>
        </li>
        <li>
            <iframe src="https://www.google.com/maps/embed?pb=!1m14!1m8!1m3!1d698.9480906272897!2d-73.5675086!3d45.5142583!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x4cc91a4b508adcab%3A0x9439f187f763ea27!2sC%C3%A9gep%20du%20Vieux%20Montr%C3%A9al!5e0!3m2!1sfr!2sfr!4v1654247064830!5m2!1sfr!2sfr" width="600" height="450" style="border:0;" allowfullscreen="" loading="lazy" referrerpolicy="no-referrer-when-downgrade"></iframe>
        </li>
    </ul>"""
, script=True)
folium.Marker(location=[45.514688,-73.566438], popup=folium.Popup(cegep, max_width=2650),).add_to(c)
c.save('maCarte.html')