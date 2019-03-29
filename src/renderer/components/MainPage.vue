<template>
  <div class="block">
    <div class="input-card" v-show="onsearch"> 
      <search-card v-if="onsearch" @search="onSubmit"></search-card>
    </div>
    <transition name="el-zoom-in-top">
      <div v-show="onresultShow" class="transition-box"> 
        <search-result ref="result" v-if="onresultShow" @onback="onBack" @onbuy="onBuy"></search-result>
      </div>
    </transition>
  </div>
</template>

<script>
  import SearchCard from './Controls/SearchCard.vue'
  import SearchResult from './Controls/SearchResult.vue'
  let fs = require('fs')
  export default {
    name: 'main-page',
    components: {
      SearchCard, SearchResult
    },
    methods: {
      onSubmit (departure, arrival, departureDate) {
        if (!departureDate) {
          this.$message({message: '请选择日期！', type: 'warning'})
          return
        }
        this.onsearch = false
        this.onresultShow = true
        // console.log(this.$refs.result)
        fs.readFile(this.path + '/lines.json', (err, data) => {
          if (!err) {
            let lines = JSON.parse(data)
            // console.log(lines)
            for (let item of lines) {
              // console.log(item.stations)
              // console.log(departure)
              for (let s = 0; s < item.stations.length - 1; s++) {
                if (departure === '' || item.stations[s].name.indexOf(departure) === 0) {
                  console.log(item.stations[s].price)
                  for (let i = s + 1; i < item.stations.length; i++) {
                    if (arrival === '' || item.stations[i].name.indexOf(arrival) === 0) {
                      let time1 = item.stations[s].time.split(':')
                      let time2 = item.stations[i].time.split(':')
                      let costmin = (parseInt(time2[0]) * 60 + parseInt(time2[1])) - (parseInt(time1[0]) * 60 + parseInt(time1[1]))
                      let hour = Math.floor(costmin / 60)
                      let mins = costmin % 60
                      let str = hour.toString() + ':' + mins.toString()
                      console.log(item.secondClass + '111')
                      this.$refs.result.tableData.push({
                        number: item.number,
                        departure: item.stations[s].name,
                        arrival: item.stations[i].name,
                        departureTime: item.stations[s].time,
                        arrivalTime: item.stations[i].time,
                        cost: str,
                        businessClass: parseInt(item.businessClass),
                        firstClass: parseInt(item.firstClass),
                        secondClass: parseInt(item.secondClass),
                        price: parseInt(item.stations[i].price) - parseInt(item.stations[s].price)
                      })
                    }
                  }
                }
              }
            }
            let dep = []
            let arr = []
            for (let item of this.$refs.result.tableData) {
              if (!dep.includes(item.departure)) {
                dep.push(item.departure)
                this.$refs.result.departureFilters.push({text: item.departure, value: item.departure})
              }
              if (!arr.includes(item.arrival)) {
                arr.push(item.arrival)
                this.$refs.result.arrivalFilters.push({text: item.arrival, value: item.arrival})
              }
            }
            console.log(dep)
            console.log(233)
            fs.readFile(this.path + '/tickets.json', (err, data) => {
              if (!err) {
                let ordersSaved = JSON.parse(data)
                // console.log(ordersSaved)
                for (let i of ordersSaved) {
                  for (let x of this.$refs.result.tableData) {
                    if (x.number === i.number) {
                      // console.log(i.number)
                      if (i.seatClass === '1') {
                        x.secondClass--
                        // console.log(x.secondClass)
                      } else if (i.seatClass === '2') {
                        x.firstClass--
                      } else if (i.seatClass === '3') {
                        x.businessClass--
                      }
                    }
                  }
                }
              }
            })
          } else {
            this.$message({message: err, type: 'warning', showClose: true})
          }
        })
        this.form.departureDate = departureDate
        this.form.departure = departure
        this.form.arrival = arrival
      },
      onBack () {
        this.onresultShow = false
        this.onsearch = true
      },
      onBuy (form) {
        let dat = []
        for (let i = 0; i < form.count; i++) { // 生成一张一张的票
          dat.push({
            number: form.number,
            seatClass: form.seatClass,
            departure: form.departure,
            arrival: form.arrival,
            date: form.date,
            departureTime: form.departureTime,
            seat: form.seat[i]
          })
        }
        // console.log(dat)
        fs.readFile(this.path + '/tickets.json', (err, data) => { // 写入文件
          if (!err) {
            let tickets = JSON.parse(data)
            let newd = tickets.concat(dat)
            fs.writeFile(this.path + '/tickets.json', JSON.stringify(newd), (err) => {
              if (!err) {
                this.$message({message: '购买成功!', type: 'success', showClose: true})
              } else {
                this.$message({message: err, type: 'warning', showClose: true})
              }
            })
          } else {
            fs.writeFile(this.path + '/tickets.json', JSON.stringify(dat), (err) => {
              if (!err) {
                this.$message({message: '购买成功!', type: 'success', showClose: true})
              } else {
                this.$message({message: err, type: 'warning', showClose: true})
              }
            })
          }
        })
      }
    },
    created () {
      const { ipcRenderer } = require('electron')
      ipcRenderer.send('get-app-path')
      ipcRenderer.on('got-app-path', (event, path) => {
        this.path = path
      })
    },
    data () {
      return {
        path: '',
        onsearch: true,
        onresultShow: false,
        form: {
          departure: '',
          arrival: '',
          departureDate: ''
        },
        tableData: [],
        departureFilters: [],
        arrivalFilters: []
      }
    }
  }
</script>

<style>
  .input{
    width: 300px;
  }
  .input-card{
    width: 400px;
    margin: 0px auto;
    border-radius: 10px;
  }
    .text-center {
    text-align: center;
    margin: 0.5rem
  }
</style>
