
const axios = require('axios')
const cheerio = require('cheerio')
const fs = require('fs')

const query = encodeURI("배방고등학교 급식")

axios.get(`https://search.naver.com/search.naver?query=${query}`).then(r =>{
    const $ = cheerio.load(r.data)
    let menu = []

    $('div.school_menu').children().children('li.menu_info').each((i,elem)=>{
        menu[i] = {}
        menu[i].date = $(elem).children('strong').text().split('[')[0].replace('월 ','-').replace('일 ','').replace(/-([1-9])$/,'-0$1')
        menu[i].list = $(elem).children('ul').children('li').map((i, elem)=>{
            return $(elem).text().replace(/\**[0-9.]+/i,'')
        }).get()
    })
    today = new Date().toISOString().substr(5, 5);
    console.log(menu)

    todaySM = menu.find(e => e.date == today)
    console.log(todaySM)

    fs.writeFileSync('./dist/todaySM.txt',todaySM.list.join('\n'))
}).catch(e => {
    console.log(e)
})